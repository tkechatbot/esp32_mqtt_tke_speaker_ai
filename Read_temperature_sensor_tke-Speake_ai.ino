// Đọc cảm biến nhiệt độ kết nối tke-Speake_ai

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Cấu hình Wi-Fi và MQTT broker
const char* ssid = "xxxxxxx";
const char* password = "xxxxxxx";
const char* mqtt_server = "192.168.xx.xx";

#define DHTPIN 4 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

// Các topic sử dụng
const char* subscribe_topic = "topic/1";
const char* publish_topic = "topic/1/response";
const char* name_device = "DHT11";

unsigned long lastMsg = 0;
char msg[50];
int value = 0;

String data_dht;

#define LED 2
#define ledPin 2
int enb_send = 0;

void blink_led(unsigned int times, unsigned int duration){
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);
    delay(duration);
    digitalWrite(ledPin, LOW); 
    delay(200);
  }
}
//=================================================
void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  while (!client.connected()) {
    if (client.connect(name_device)) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(subscribe_topic);
    } 
    else {
      delay(2000);
        }
    }
}
//=================================================
void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi đã kết nối");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
//=================================================
void callback(char* topic, byte* payload, unsigned int length) {
    String data_text;
    for (int i = 0; i < length; i++) {
        data_text += (char)payload[i];
    }
    Serial.println(topic);
    Serial.println(data_text);

    if(String(topic)== subscribe_topic){
        const char* str = data_text.c_str(); 
        if (strstr(str, "phòng") && strstr(str, "khách")) {  // Kiểm tra từ "nhiệt" và "phòng" trong chuỗi
          Serial.println("Send_data");
          client.publish(publish_topic,data_dht.c_str());
        } 
        else {
          Serial.println("No text");
        }
    
  // Điều khiển ON/OFF relay
  //  if( data_text == "mở quạt"){
  //    Serial.println("OK-ON");
  //    client.publish(publish_topic,"complete");  // trả vể điều khiển thành công
  //  }
  //  if( data_text == "tắt quạt"){
  //    Serial.println("OK-OFF");
  //    client.publish(publish_topic,"complete");
  //  }
          data_text = "";  
      }
}
//==========================================
void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        if(WiFi.status() != WL_CONNECTED){
          setup_wifi();
        }
    Serial.print("Đang kết nối tới MQTT broker...");
    while (!client.connected()) {
        if (client.connect(name_device)) {
          Serial.println("Connected to MQTT broker");
          client.subscribe(subscribe_topic);
        } 
        else {
          Serial.print("Thất bại, rc=");
          Serial.print(client.state());
          Serial.println(" Thử lại trong 5 giây");
          blink_led(3,200); //blink LED three
          delay(2000);
        }
    }
  }
}
//=================================================
void loop() {
   if (!client.connected()) {
    reconnect();
  }
  client.loop();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  char humidity[6];
  dtostrf(h, 4, 1, humidity);  // Chuyển float thành chuỗi
  char temp[6];
  dtostrf(t, 4, 1, temp);  // Chuyển float thành chuỗi
  data_dht = "nhiệt độ phòng khách là "+ String(temp)+ "°C " + "độ ẩm " + String(humidity)+ "%";  // Nối chuỗi
  //client.publish(publish_topic,data_dht.c_str());
  //Serial.println(data_dht);  // In kết quả nối chuỗi
  delay(500);
  }
