#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <RCSwitch.h>


#include "esp32_mqtt.h"


//client.publish(publish_topic,"complete");  // Send
//const char* subscribe_topic = "topic/1";
//const char* publish_topic = "topic/1/response";
//const char* name_device = "ESP32Client1";

const char* ssid = "TKE24h_2.4";
const char* password = "supercuibap123";

const char* ssid_ap = "ESP32-AP";
const char* password_ap = "12345678";

IPAddress local_IP(192, 168, 42, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);
DNSServer dnsServer;

#define ledPin 2
#define wifiLed 2
int mode_AP = 0;

//--------------------------------------------------------------
void read_eeprom(){
check_rl1 = bool(EEPROM.read(1));
check_rl2 = bool(EEPROM.read(2));
check_rl3 = bool(EEPROM.read(3));
check_rl4 = bool(EEPROM.read(4));
check_rl5 = bool(EEPROM.read(5));
check_rl6 = bool(EEPROM.read(6));
check_rl7 = bool(EEPROM.read(7));
check_rl8 = bool(EEPROM.read(8));
check_rl9 = bool(EEPROM.read(9)); 
check_rl10 = bool(EEPROM.read(10));
check_rl11 = bool(EEPROM.read(11));
check_rl12 = bool(EEPROM.read(12));
check_rl13 = bool(EEPROM.read(13));
check_rl14 = bool(EEPROM.read(14));
check_rl15 = bool(EEPROM.read(15));
check_rl16 = bool(EEPROM.read(16));
}
//=========================================================
void choptat_led()
{
for (k = 0; k<= 4; k++) {
digitalWrite(wifiLed,HIGH);
delay(200);
digitalWrite(wifiLed,LOW);
delay(200);}
}
//=========================================================
void choptat_learning()
{
for (k = 0; k<= 20; k++) {
digitalWrite(wifiLed,HIGH);
delay(40);
digitalWrite(wifiLed,LOW);
delay(40);}
}
//==============Ngat Reset nhan remote 1 lan=================
void IRAM_ATTR onTimer(){
  ++count_tke;
  if(count_tke >40){ 
    count_tke=0;
    if(con_wifi == 0){digitalWrite(wifiLed,!(digitalRead(wifiLed)));}  //Toggle LED Pin
    read_loop = 0;
  }
}
//===========================================
void blink_led(unsigned int times, unsigned int duration){
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);
    delay(duration);
    digitalWrite(ledPin, LOW); 
    delay(200);
  }
}
//------------------------------------------------
void writeLongIntoEEPROM(int address, long number)
{ 
  EEPROM.write(address, (number >> 24) & 0xFF);
  EEPROM.write(address + 1, (number >> 16) & 0xFF);
  EEPROM.write(address + 2, (number >> 8) & 0xFF);
  EEPROM.write(address + 3, number & 0xFF);
}
long readLongFromEEPROM(int address)
{
  return ((long)EEPROM.read(address) << 24) +
         ((long)EEPROM.read(address + 1) << 16) +
         ((long)EEPROM.read(address + 2) << 8) +
         (long)EEPROM.read(address + 3);
}
//=========================================== 
void setup_wifi() {
  int c=0;
  delay(10);
  //WiFi.begin(ssid, password);
  
  WiFi.begin(Wifi_ssid,Wifi_password);          // Kết nối lấy tên wifi+pass từ eeprom
  Serial.println("Connected to Wi-Fi!");
  while (WiFi.status() != WL_CONNECTED) {
      c=c+1;
      delay(500);
      Serial.print(".");
      if(c>40){
          break; 
      }
  }
  Serial.println("");
  Serial.println("WiFi đã kết nối");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
//========================================================
void send_complete(){
  client.publish(publish_topic,"complete");
}

//=================================================
void callback(char* topic, byte* payload, unsigned int length) {
    String message;
    int enb_send = 0;
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println(topic);
    Serial.println(message);
    if(String(topic)== subscribe_topic){
        Serial.println("topic_OK");
        if(message == textOn_relay1){
          bitClear(status_relay_8,0);
          enb_send = 1;
          update_595_8();
          EEPROM.write(1,0);
          EEPROM.commit();  
          }
        if(message == textOff_relay1){
          bitSet(status_relay_8,0);
          enb_send = 1;
          update_595_8();
          EEPROM.write(1,1);
          EEPROM.commit(); 
          }
        //---------------------  
        if(message == textOn_relay2){
          bitClear(status_relay_8,1);
          enb_send = 1;
          update_595_8();
          EEPROM.write(2,0); 
          EEPROM.commit(); 
          }
        if(message == textOff_relay2){
          bitSet(status_relay_8,1);
          enb_send = 1;
          update_595_8();
          EEPROM.write(2,1);
          EEPROM.commit(); 
          }
        //---------------------  
        if(message == textOn_relay3){
          bitClear(status_relay_8,2);
          enb_send = 1;
          update_595_8();
          EEPROM.write(3,0); 
          EEPROM.commit(); 
          }
        if(message == textOff_relay3){
          bitSet(status_relay_8,2);
          enb_send = 1;
          update_595_8();
          EEPROM.write(3,1);
          EEPROM.commit(); 
          }
        //---------------------  
        if(message == textOn_relay4){
          bitClear(status_relay_8,3);
          enb_send = 1;
          update_595_8();
          EEPROM.write(4,0);
          EEPROM.commit();  
          }
        if(message == textOff_relay4){
          bitSet(status_relay_8,3);
          enb_send = 1;
          update_595_8();
          EEPROM.write(4,1); 
          EEPROM.commit();
          }
        //---------------------  
        if(message == textOn_relay5){
          bitClear(status_relay_8,4);
          enb_send = 1;
          update_595_8();
          EEPROM.write(5,0);
          EEPROM.commit();  
          }
        if(message == textOff_relay5){
          bitSet(status_relay_8,4);
          enb_send = 1;
          update_595_8();
          EEPROM.write(5,1);
          EEPROM.commit(); 
          }
        //---------------------  
        if(message == textOn_relay6){
          bitClear(status_relay_8,5);
          enb_send = 1;
          update_595_8();
          EEPROM.write(6,0);
          EEPROM.commit();  
          }
        if(message == textOff_relay6){
          bitSet(status_relay_8,5);
          enb_send = 1;
          update_595_8();
          EEPROM.write(6,1);
          EEPROM.commit(); 
          }
        //---------------------  
        if(message == textOn_relay7){
          bitClear(status_relay_8,6);
          enb_send = 1;
          update_595_8();
          EEPROM.write(7,0);
          EEPROM.commit();  
          }
        if(message == textOff_relay7){
          bitSet(status_relay_8,6);
          enb_send = 1;
          update_595_8();
          EEPROM.write(7,1);
          EEPROM.commit(); 
          }
        //---------------------  
        if(message == textOn_relay8){
          bitClear(status_relay_8,7);
          enb_send = 1;
          update_595_8();
          EEPROM.write(8,0);
          EEPROM.commit();  
          }
        if(message == textOff_relay8){
          bitSet(status_relay_8,7);
          enb_send = 1;
          update_595_8();
          EEPROM.write(8,1);
          EEPROM.commit(); 
          }
        //---------------------  
        if(message == textOn_relay9){
          bitClear(status_relay_7,1);
          enb_send = 1;
          update_595_7();
          EEPROM.write(9,0); 
          EEPROM.commit(); 
          }
        if(message == textOff_relay9){
          bitSet(status_relay_7,1);
          enb_send = 1;
          update_595_7();
          EEPROM.write(9,1); 
          EEPROM.commit();
          }
        //---------------------  
        if(message == textOn_relay10){
          bitClear(status_relay_7,2);
          enb_send = 1;
          update_595_7();
          EEPROM.write(10,0);
          EEPROM.commit();  
          }
        if(message == textOff_relay10){
          bitSet(status_relay_7,2);
          enb_send = 1;
          update_595_7();
          EEPROM.write(10,1);
          EEPROM.commit(); 
        }
        //---------------------  
        if(message == textOn_relay11){
          bitClear(status_relay_7,3);
          enb_send = 1;
          update_595_7();
          EEPROM.write(11,0);
          EEPROM.commit();  
          }
        if(message == textOff_relay11){
          bitSet(status_relay_7,3);
          enb_send = 1;
          update_595_7();
          EEPROM.write(11,1);
          EEPROM.commit();
        }

        //---------------------  
        if(message == textOn_relay12){
          bitClear(status_relay_7,4);
          enb_send = 1;
          update_595_7();
          EEPROM.write(12,0); 
          EEPROM.commit(); 
          }
        if(message == textOff_relay12){
          bitSet(status_relay_7,4);
          enb_send = 1;
          update_595_7();
          EEPROM.write(12,1);
          EEPROM.commit();
        }

        //---------------------  
        if(message == textOn_relay13){
          bitClear(status_relay_7,5);
          enb_send = 1;
          update_595_7();
          EEPROM.write(13,0);
          EEPROM.commit();  
          }
        if(message == textOff_relay13){
          bitSet(status_relay_7,5);
          enb_send = 1;
          update_595_7();
          EEPROM.write(13,1);
          EEPROM.commit();
        }

        //---------------------  
        if(message == textOn_relay14){
          bitClear(status_relay_7,6);
          enb_send = 1;
          update_595_7();
          EEPROM.write(14,0);
          EEPROM.commit();  
          }
        if(message == textOff_relay14){
          bitSet(status_relay_7,6);
          enb_send = 1;
          update_595_7();
          EEPROM.write(14,1);
          EEPROM.commit();
        }
        //---------------------  
        if(message == textOn_relay15){
          bitClear(status_relay_7,7);
          enb_send = 1;
          update_595_7();
          EEPROM.write(15,0); 
          EEPROM.commit(); 
          }
        if(message == textOff_relay15){
          bitSet(status_relay_7,7);
          enb_send = 1;
          update_595_7();
          EEPROM.write(15,1); 
          EEPROM.commit(); 
        }
          
        if((message == textOn_all)||(message == textOn_all2)){
          relay_on_all();
          enb_send = 1;
        }
        if((message == textOff_all)||(message == textOff_all2)){
          relay_off_all();
          enb_send = 1;
        }
          
        if(enb_send == 1){
          enb_send =0;
          client.publish(publish_topic,"complete");
        }
          enb_send = 0;  
          message = "";  

      }
}
//===========================================================
void relay_on_all(){
          status_relay_8=0;
          status_relay_7=0;
          update_595_7();
          update_595_8();
          EEPROM.write(16,1); 
          EEPROM.write(1,1); 
          EEPROM.write(2,1); 
          EEPROM.write(3,1); 
          EEPROM.write(4,1); 
          EEPROM.write(5,1); 
          EEPROM.write(6,1); 
          EEPROM.write(7,1); 
          EEPROM.write(8,1); 
          EEPROM.write(9,1); 
          EEPROM.write(10,1); 
          EEPROM.write(11,1); 
          EEPROM.write(12,1); 
          EEPROM.write(13,1); 
          EEPROM.write(14,1); 
          EEPROM.write(15,1); 
          EEPROM.commit();
}
//===========================================================
void relay_off_all(){
          status_relay_8=255;
          status_relay_7=255;
          update_595_7();
          update_595_8();
          EEPROM.write(16,0); 
          EEPROM.write(1,0);
          EEPROM.write(2,0);
          EEPROM.write(3,0);
          EEPROM.write(4,0);
          EEPROM.write(5,0); 
          EEPROM.write(6,0); 
          EEPROM.write(7,0); 
          EEPROM.write(8,0);
          EEPROM.write(9,0);
          EEPROM.write(10,0); 
          EEPROM.write(11,0); 
          EEPROM.write(12,0); 
          EEPROM.write(13,0);
          EEPROM.write(14,0);
          EEPROM.write(15,0);
          EEPROM.commit();
}

//-----------------------------------------------------------
void relay_status(){
    if(check_rl1==1){ bitClear(status_relay_8,0);delay(100);}
         else { bitSet(status_relay_8,0);delay(100);}
    if(check_rl2==1){ bitClear(status_relay_8,1);delay(100);}
         else {bitSet(status_relay_8,1);delay(100);}
    if(check_rl3==1){bitClear(status_relay_8,2);delay(100);}
         else {bitSet(status_relay_8,2); delay(100);}
    if(check_rl4==1){bitClear(status_relay_8,3);delay(100);}
         else {bitSet(status_relay_8,3); delay(100);}
    if(check_rl5==1){bitClear(status_relay_8,4);delay(100);}
         else {bitSet(status_relay_8,4);delay(100);}
    if(check_rl6==1){bitClear(status_relay_8,5);delay(100);}
         else {bitSet(status_relay_8,5);delay(100);}
    if(check_rl7==1){bitClear(status_relay_8,6);delay(100);}
         else {bitSet(status_relay_8,6);delay(100);}    
    if(check_rl8==1){bitClear(status_relay_8,7);delay(100);}
         else {bitSet(status_relay_8,7);delay(100);}
         update_595_8();
    
    if(check_rl9==1){bitClear(status_relay_7,1);delay(100);}
         else {bitSet(status_relay_7,1);delay(100);}
    if(check_rl10==1){bitClear(status_relay_7,2);delay(100);}
         else {bitSet(status_relay_7,2);delay(100);}
    if(check_rl11==1){bitClear(status_relay_7,3);delay(100);}
         else {bitSet(status_relay_7,3);delay(100);}
    if(check_rl12==1){bitClear(status_relay_7,4);delay(100);}
         else {bitSet(status_relay_7,4);delay(100);}   
    if(check_rl13==1){bitClear(status_relay_7,5);delay(100);}
         else {bitSet(status_relay_7,5);delay(100);}
    if(check_rl14==1){bitClear(status_relay_7,6);delay(100);}
         else {bitSet(status_relay_7,6);delay(100);}
    if(check_rl15==1){bitClear(status_relay_7,7);delay(100);}
         else {bitSet(status_relay_7,7);delay(100);}
    update_595_7();
    
}

//---------------------------------------------------------------
void update_595_8()
{
   digitalWrite(latchPin_8, LOW);
   shiftOut(dataPin_8, clockPin_8, LSBFIRST,status_relay_8);
   digitalWrite(latchPin_8, HIGH);
}
void update_595_7()
{
   digitalWrite(latchPin_7, LOW);
   shiftOut(dataPin_7, clockPin_7, LSBFIRST,status_relay_7);
   digitalWrite(latchPin_7, HIGH);
}
//------------------------------------------------------------------------------
void reset_relay_all(){
    status_relay_8=255;    // Set the bit that controls that LED in the variable 'leds'
    status_relay_7=255; 
    update_595_8();
    update_595_7();
}
//================================================
void setup() {
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);
  pinMode(gpio_reset, INPUT);
  
    pinMode(latchPin_8, OUTPUT);
    pinMode(dataPin_8, OUTPUT);  
    pinMode(clockPin_8, OUTPUT);
    pinMode(latchPin_7, OUTPUT);
    pinMode(dataPin_7, OUTPUT);  
    pinMode(clockPin_7, OUTPUT);

    pinMode(OE7, OUTPUT);
    pinMode(OE8, OUTPUT);
    digitalWrite(OE7,HIGH);
    digitalWrite(OE8,HIGH); 

    reset_relay_all();
    while (!EEPROM.begin(4049)){true;}
    read_eeprom();
    digitalWrite(OE7,LOW);
    delay(20);
    relay_status();
    pinMode(wifiLed, OUTPUT);
    digitalWrite(wifiLed,HIGH);
    
  
    pinMode( RF_RECEIVER, INPUT_PULLUP ); 
    mySwitch.enableReceive(RF_RECEIVER);  // Receiver on interrupt 0
    delay(100);
    coppy_L1=0;
    con_wifi = 0; // biến báo mất kết nối wifi 
    
 
    read_eeprom_system();  // Đọc eeprom lấy name + pass wifi 

    setup_wifi();  //kết nối Wi-Fi
    delay(1000);

  if (WiFi.status() != WL_CONNECTED) {    // Nếu không kết nối được, phát AP
      con_wifi = 0;
      delay(500);
      WiFi.disconnect(true); // Ngắt kết nối và tắt chế độ STA
      WiFi.mode(WIFI_OFF);   // Tắt hoàn toàn chức năng WiFi (STA + AP)
      Serial.println("STA mode disabled");
        
      WiFi.softAPConfig(local_IP, gateway, subnet);
      WiFi.softAP(ssid_ap, password_ap);
      dnsServer.start(53, "*", local_IP);// Bắt đầu DNS server để chuyển hướng
      server.on("/", handleRoot); // Thiết lập các route cho server
      server.on("/submit", handleSubmit);
      server.begin();
      Serial.println("AP Mode");
      mode_AP = 1;
      } 
  else {
        con_wifi = 1;
        mode_AP = 0;
        Serial.println("Connected to MQTT broker?????");
        client.setServer(mqtt_server, 1883);
        client.setCallback(callback);
        while (!client.connected()) {
            if (client.connect(name_device)) {
            Serial.println("Connected to MQTT broker");
            client.subscribe(subscribe_topic);
          } 
            else {
                delay(5000);
                  }
            blink_led(3,200); //blink LED three   
         }
      }
      
    My_timer = timerBegin(0, 80, true);
    timerAttachInterrupt(My_timer, &onTimer, true);
    timerAlarmWrite(My_timer, 10000, true);
    timerAlarmEnable(My_timer);

    delay(500);
    reard_eeprom_rm();
    count_tke=0;
    read_loop = 0;
}
//==========================================
void reconnect() {
      while (!client.connected()) {
        if(WiFi.status() != WL_CONNECTED){
          setup_wifi();
        }
        Serial.print("Đang kết nối tới MQTT broker...");
        if (client.connect(name_device)) {
            Serial.println("Connected to MQTT broker");
            client.subscribe(subscribe_topic);
           
        } 
        else {
            Serial.print("Thất bại, rc=");
            Serial.print(client.state());
            Serial.println(" Thử lại trong 5 giây");
            blink_led(3,200); //blink LED three
            delay(3000);
            }
        }
}
//---------------------------------------------------------
void off_all_relay_setup(){
    status_relay_8=255;    // Set the bit that controls that LED in the variable 'leds'
    status_relay_7=255; 
    update_595_8();
    update_595_7();
}
//======================================================
void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
  if(mode_AP ==0){
      if (!client.connected()) {
          reconnect();
        }
        client.loop();
      }
  if((digitalRead(SwitchPin2) == LOW)&&(digitalRead(SwitchPin3) == LOW)){
        Serial.printf("Reset Button Pressed!\n");
        delay(100);
        int startTime = millis();
        digitalWrite(wifiLed,LOW);
        while((digitalRead(SwitchPin2) == LOW)&&(digitalRead(SwitchPin3) == LOW));delay(50);
        int endTime = millis();
        if ((endTime - startTime) > 30000) { // If key pressed for more than 10secs, reset all
          Serial.printf("Reset to factory.\n");
        // reset device all
          choptat_learning();
        } else if ((endTime - startTime) > 10000) {
          Serial.printf("Reset Wi-Fi.\n");
          reset_name_wifi();
          choptat_learning();
        }
  }
  rf_remote();
  key();
}
//======================================================
void rf_remote(){
  if (mySwitch.available()){
    count_tke=0;          // reset timer
    Serial.println(mySwitch.getReceivedValue());
    digitalWrite(wifiLed,LOW);
    if(read_loop == 0){ 
      read_loop = 1;
      data_rf += mySwitch.getReceivedValue();
      code_remote = data_rf.toInt();
     // Serial.println(code_remote);
      count_tke=0;;
     if(learning_remote == true){eeprom_remote();}
     if(learning_remote == false){on_off_relay();}    
  }
    mySwitch.resetAvailable();
    data_rf = "";
    digitalWrite(wifiLed,LOW);
  }
}
//======================================================
void key(){
if ( digitalRead(SwitchPin1) == LOW ) { 
    for (k = 0; k<= 3000; k++) {
    delay(1);
    if ( digitalRead(SwitchPin1) == HIGH ) {m =1; goto tke_1;}
   }
   m=0;
   off_all_relay_setup();
   choptat_led();
   learning_remote=true;   // cho phep hoc remote
   learning_relay=0;
}
if(learning_remote == true){
if ( digitalRead(SwitchPin3) == LOW) {delay(300); // UP
   while( digitalRead(SwitchPin3) == LOW); 
   check_code=0;
   learning_relay++;
   if(learning_relay==16){learning_relay=1;}
   if(learning_relay==1){bitClear(status_relay_8,0);update_595_8();} else{bitSet(status_relay_8,0);update_595_8();}
   if(learning_relay==2){bitClear(status_relay_8,1);update_595_8();} else{bitSet(status_relay_8,1);update_595_8();}
   if(learning_relay==3){bitClear(status_relay_8,2);update_595_8();} else{bitSet(status_relay_8,2);update_595_8();}
   if(learning_relay==4){bitClear(status_relay_8,3);update_595_8();} else{bitSet(status_relay_8,3);update_595_8();}
   if(learning_relay==5){bitClear(status_relay_8,4);update_595_8();} else{bitSet(status_relay_8,4);update_595_8();}
   if(learning_relay==6){bitClear(status_relay_8,5);update_595_8();} else{bitSet(status_relay_8,5);update_595_8();}
   if(learning_relay==7){bitClear(status_relay_8,6);update_595_8();} else{bitSet(status_relay_8,6);update_595_8();}
   if(learning_relay==8){bitClear(status_relay_8,7);update_595_8();} else{bitSet(status_relay_8,7);update_595_8();}
   if(learning_relay==9){bitClear(status_relay_7,1);update_595_7();} else{bitSet(status_relay_7,1);update_595_7();}
   if(learning_relay==10){bitClear(status_relay_7,2);update_595_7();} else{bitSet(status_relay_7,2);update_595_7();}
   if(learning_relay==11){bitClear(status_relay_7,3);update_595_7();} else{bitSet(status_relay_7,3);update_595_7();}
   if(learning_relay==12){bitClear(status_relay_7,4);update_595_7();} else{bitSet(status_relay_7,4);update_595_7();}
   if(learning_relay==13){bitClear(status_relay_7,5);update_595_7();} else{bitSet(status_relay_7,5);update_595_7();}
   if(learning_relay==14){bitClear(status_relay_7,6);update_595_7();} else{bitSet(status_relay_7,6);update_595_7();}   
   if(learning_relay==15){bitClear(status_relay_7,7);update_595_7();} else{bitSet(status_relay_7,7);update_595_7();}
}
if ( digitalRead(SwitchPin2) == LOW) {delay(300);  // Down
   while( digitalRead(SwitchPin2) == LOW);
   check_code=0;
   learning_relay--;
   if(learning_relay==0){learning_relay=15;}
   if(learning_relay==1){bitClear(status_relay_8,0);update_595_8();} else{bitSet(status_relay_8,0);update_595_8();}
   if(learning_relay==2){bitClear(status_relay_8,1);update_595_8();} else{bitSet(status_relay_8,1);update_595_8();}
   if(learning_relay==3){bitClear(status_relay_8,2);update_595_8();} else{bitSet(status_relay_8,2);update_595_8();}
   if(learning_relay==4){bitClear(status_relay_8,3);update_595_8();} else{bitSet(status_relay_8,3);update_595_8();}
   if(learning_relay==5){bitClear(status_relay_8,4);update_595_8();} else{bitSet(status_relay_8,4);update_595_8();}
   if(learning_relay==6){bitClear(status_relay_8,5);update_595_8();} else{bitSet(status_relay_8,5);update_595_8();}
   if(learning_relay==7){bitClear(status_relay_8,6);update_595_8();} else{bitSet(status_relay_8,6);update_595_8();}
   if(learning_relay==8){bitClear(status_relay_8,7);update_595_8();} else{bitSet(status_relay_8,7);update_595_8();}
   if(learning_relay==9){bitClear(status_relay_7,1);update_595_7();} else{bitSet(status_relay_7,1);update_595_7();}
   if(learning_relay==10){bitClear(status_relay_7,2);update_595_7();} else{bitSet(status_relay_7,2);update_595_7();}
   if(learning_relay==11){bitClear(status_relay_7,3);update_595_7();} else{bitSet(status_relay_7,3);update_595_7();}
   if(learning_relay==12){bitClear(status_relay_7,4);update_595_7();} else{bitSet(status_relay_7,4);update_595_7();}
   if(learning_relay==13){bitClear(status_relay_7,5);update_595_7();} else{bitSet(status_relay_7,5);update_595_7();}
   if(learning_relay==14){bitClear(status_relay_7,6);update_595_7();} else{bitSet(status_relay_7,6);update_595_7();}  
   if(learning_relay==15){bitClear(status_relay_7,7);update_595_7();} else{bitSet(status_relay_7,7);update_595_7();}
}
if (digitalRead(SwitchPin4) == LOW ) {    // Delete code remote
    for (k = 0; k<= 3000; k++) {
    delay(1);
   if ( digitalRead(SwitchPin4) == HIGH ) {goto ex1;}}
   if(learning_relay==1){for(del=100;del<=110;del++){EEPROM.write(del,0);} EEPROM.write(71,3);}
   if(learning_relay==2){for(del=111;del<=120;del++){EEPROM.write(del,0);} EEPROM.write(72,3);}
   if(learning_relay==3){for(del=121;del<=130;del++){EEPROM.write(del,0);} EEPROM.write(73,3);}
   if(learning_relay==4){for(del=131;del<=140;del++){EEPROM.write(del,0);} EEPROM.write(74,3);}
   if(learning_relay==5){for(del=141;del<=150;del++){EEPROM.write(del,0);} EEPROM.write(75,3);}
   if(learning_relay==6){for(del=151;del<=160;del++){EEPROM.write(del,0);} EEPROM.write(76,3);}
   if(learning_relay==7){for(del=161;del<=170;del++){EEPROM.write(del,0);} EEPROM.write(77,3);}
   if(learning_relay==8){for(del=171;del<=180;del++){EEPROM.write(del,0);} EEPROM.write(78,3);}
   if(learning_relay==9){for(del=181;del<=190;del++){EEPROM.write(del,0);} EEPROM.write(79,3);}
   if(learning_relay==10){for(del=191;del<=200;del++){EEPROM.write(del,0);} EEPROM.write(80,3);}
   if(learning_relay==11){for(del=201;del<=210;del++){EEPROM.write(del,0);} EEPROM.write(81,3);}
   if(learning_relay==12){for(del=211;del<=220;del++){EEPROM.write(del,0);} EEPROM.write(82,3);}
   if(learning_relay==13){for(del=221;del<=230;del++){EEPROM.write(del,0);} EEPROM.write(83,3);}
   if(learning_relay==14){for(del=231;del<=240;del++){EEPROM.write(del,0);} EEPROM.write(84,3);}
   if(learning_relay==15){for(del=241;del<=250;del++){EEPROM.write(del,0);} EEPROM.write(85,3);}
   EEPROM.commit();
   choptat_learning();
ex1:;
}
}
tke_1: if(m==1){m=0;learning_remote = false;ESP.restart();Serial.printf("learning_remote = false");learning_relay=0;}
}

//------------------------------------------------ 
void reard_eeprom_rm(){
   code_rm1_on = readLongFromEEPROM(100);
   code_rm1_off = readLongFromEEPROM(110);
   code_rm2_on = readLongFromEEPROM(111);
   code_rm2_off = readLongFromEEPROM(120);
   code_rm3_on = readLongFromEEPROM(121);
   code_rm3_off = readLongFromEEPROM(130); 
   code_rm4_on = readLongFromEEPROM(131);
   code_rm4_off = readLongFromEEPROM(140);
   code_rm5_on = readLongFromEEPROM(141);
   code_rm5_off = readLongFromEEPROM(150);   
   code_rm6_on = readLongFromEEPROM(151);
   code_rm6_off = readLongFromEEPROM(160);
   code_rm7_on = readLongFromEEPROM(161);
   code_rm7_off = readLongFromEEPROM(170);
   code_rm8_on = readLongFromEEPROM(171);
   code_rm8_off = readLongFromEEPROM(180);
   code_rm9_on = readLongFromEEPROM(181);
   code_rm9_off = readLongFromEEPROM(190);
   code_rm10_on = readLongFromEEPROM(191);
   code_rm10_off = readLongFromEEPROM(200);
   code_rm11_on = readLongFromEEPROM(201);
   code_rm11_off = readLongFromEEPROM(210);
   code_rm12_on = readLongFromEEPROM(211);
   code_rm12_off = readLongFromEEPROM(220);   
   code_rm13_on = readLongFromEEPROM(221);
   code_rm13_off = readLongFromEEPROM(230); 
   code_rm14_on = readLongFromEEPROM(231);
   code_rm14_off = readLongFromEEPROM(240);
   code_rm15_on = readLongFromEEPROM(241);
   code_rm15_off = readLongFromEEPROM(250);
    
             
   select_1 = int(EEPROM.read(71)); 
   select_2 = int(EEPROM.read(72));
   select_3 = int(EEPROM.read(73));
   select_4 = int(EEPROM.read(74));
   select_5 = int(EEPROM.read(75));
   select_6 = int(EEPROM.read(76));
   select_7 = int(EEPROM.read(77));
   select_8 = int(EEPROM.read(78));
   select_9 = int(EEPROM.read(79));
   select_10 = int(EEPROM.read(80));
   select_11 = int(EEPROM.read(81));
   select_12 = int(EEPROM.read(82));
   select_13 = int(EEPROM.read(83));
   select_14 = int(EEPROM.read(84));
   select_15 = int(EEPROM.read(85));
}

//=======================================================
void eeprom_remote(){
  if(code_remote > 0){
     if(learning_relay==1){ 
        coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(100, code_remote);EEPROM.write(71,0);
        bitSet(status_relay_8,0);
        update_595_8();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x1;} 
        writeLongIntoEEPROM(110, code_remote);EEPROM.write(71,1);
x1:     coppy_L1=0;check_code=0; 
        bitClear(status_relay_8,0);
        update_595_8();
     }
   }
     if(learning_relay==2){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(111, code_remote);EEPROM.write(72,0);
        bitSet(status_relay_8,1);
        update_595_8();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x2;} 
        writeLongIntoEEPROM(120, code_remote);EEPROM.write(72,1);
x2:     coppy_L1=0;check_code=0; 
        bitClear(status_relay_8,1);
        update_595_8();
     }
   }
     if(learning_relay==3){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(121, code_remote);EEPROM.write(73,0);
        bitSet(status_relay_8,2);
        update_595_8();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x3;} 
        writeLongIntoEEPROM(130, code_remote);EEPROM.write(73,1);
x3:     coppy_L1=0;check_code=0; 
        bitClear(status_relay_8,2);
        update_595_8();
     }
   }
     if(learning_relay==4){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(131, code_remote);EEPROM.write(74,0);
        bitSet(status_relay_8,3);
        update_595_8();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x4;} 
        writeLongIntoEEPROM(140, code_remote);EEPROM.write(74,1);
x4:     coppy_L1=0;check_code=0; 
        bitClear(status_relay_8,3);
        update_595_8();
     }
   }
     if(learning_relay==5){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(141, code_remote);EEPROM.write(75,0);
        bitSet(status_relay_8,4);
        update_595_8();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x5;} 
        writeLongIntoEEPROM(150, code_remote);EEPROM.write(75,1);
x5:     coppy_L1=0;check_code=0; 
        bitClear(status_relay_8,4);
        update_595_8();
     }
   }
     if(learning_relay==6){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(151, code_remote);EEPROM.write(76,0);
        bitSet(status_relay_8,5);
        update_595_8();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x6;} 
        writeLongIntoEEPROM(160, code_remote);EEPROM.write(76,1);
x6:     coppy_L1=0;check_code=0; 
        bitClear(status_relay_8,5);
        update_595_8();
     }
   }
     if(learning_relay==7){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(161, code_remote);EEPROM.write(77,0);
        bitSet(status_relay_8,6);
        update_595_8();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x7;} 
        writeLongIntoEEPROM(170, code_remote);EEPROM.write(77,1);
x7:     coppy_L1=0;check_code=0; 
        bitClear(status_relay_8,6);
        update_595_8();
     }
   }

     if(learning_relay==8){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(171, code_remote);EEPROM.write(78,0);
        bitSet(status_relay_8,7);
        update_595_8();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x8;} 
        writeLongIntoEEPROM(180, code_remote);EEPROM.write(78,1);
x8:     coppy_L1=0;check_code=0; 
        bitClear(status_relay_8,7);
        update_595_8();
     }
   }
     if(learning_relay==9){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(181, code_remote);EEPROM.write(79,0);
        bitSet(status_relay_7,1);
        update_595_7();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x9;} 
        writeLongIntoEEPROM(190, code_remote);EEPROM.write(79,1);
x9:     coppy_L1=0;check_code=0; 
        bitClear(status_relay_7,1);
        update_595_7();
     }
   }
     if(learning_relay==10){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(191, code_remote);EEPROM.write(80,0);
        bitSet(status_relay_7,2);
        update_595_7();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x10;} 
        writeLongIntoEEPROM(200, code_remote);EEPROM.write(80,1);
x10:     coppy_L1=0;check_code=0; 
        bitClear(status_relay_7,2);
        update_595_7();
     }
   }
     if(learning_relay==11){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(201, code_remote);EEPROM.write(81,0);
        bitSet(status_relay_7,3);
        update_595_7();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x11;} 
        writeLongIntoEEPROM(210, code_remote);EEPROM.write(81,1);
x11:    coppy_L1=0;check_code=0; 
        bitClear(status_relay_7,3);
        update_595_7();
     }
   }
     if(learning_relay==12){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(211, code_remote);EEPROM.write(82,0);
        bitSet(status_relay_7,4);
        update_595_7();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x12;} 
        writeLongIntoEEPROM(220, code_remote);EEPROM.write(82,1);
x12:    coppy_L1=0;check_code=0; 
        bitClear(status_relay_7,4);
        update_595_7();
     }
   }
     if(learning_relay==13){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(221, code_remote);EEPROM.write(83,0);
        bitSet(status_relay_7,5);
        update_595_7();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x13;} 
        writeLongIntoEEPROM(230, code_remote);EEPROM.write(83,1);
x13:    coppy_L1=0;check_code=0; 
        bitClear(status_relay_7,5);
        update_595_7();
     }
   }
     if(learning_relay==14){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(231, code_remote);EEPROM.write(84,0);
        bitSet(status_relay_7,6);
        update_595_7();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x14;} 
        writeLongIntoEEPROM(240, code_remote);EEPROM.write(84,1);
x14:    coppy_L1=0;check_code=0; 
        bitClear(status_relay_7,6);
        update_595_7();
     }
   }
     if(learning_relay==15){coppy_L1++;
     if(coppy_L1==1){ 
        writeLongIntoEEPROM(241, code_remote);EEPROM.write(85,0);
        bitSet(status_relay_7,7);
        update_595_7();
        check_code = code_remote;
     }
     if(coppy_L1==2){
        if(check_code == code_remote){goto x15;} 
        writeLongIntoEEPROM(250, code_remote);EEPROM.write(85,1);
x15:    coppy_L1=0;check_code=0; 
        bitClear(status_relay_7,7);
        update_595_7();
     }
   }
     EEPROM.commit();  
     choptat_learning();   
  }
  code_remote = 0;
  reard_eeprom_rm();
  learning_remote=true;  
}
//-----------------------------------------------------------------------------
void on_off_relay(){
      count_tke=0;
if(code_rm1_on == code_remote){   
      if(select_1==0){
      if(bitRead(status_relay_8,0)==1){ bitClear(status_relay_8,0);update_595_8();EEPROM.write(1,1);   //on
                                      goto rl1;} 
      if(bitRead(status_relay_8,0)==0){ bitSet(status_relay_8,0);update_595_8();EEPROM.write(1,0); // off 
                                      }        
      }
rl1:  if(select_1==1){bitClear(status_relay_8,0);update_595_8();EEPROM.write(1,1);}  // on
      }
if(code_rm1_off == code_remote){
      if(select_1==1){bitSet(status_relay_8,0);update_595_8();EEPROM.write(1,0);}   // off
}

if(code_rm2_on == code_remote){   
      if(select_2==0){
      if(bitRead(status_relay_8,1)==1){ bitClear(status_relay_8,1);update_595_8();EEPROM.write(2,1);   //on
                                        goto rl2;} 
      if(bitRead(status_relay_8,1)==0){ bitSet(status_relay_8,1);update_595_8();EEPROM.write(2,0); // off 
                                      }        
      }
rl2:  if(select_2==1){bitClear(status_relay_8,1);update_595_8();EEPROM.write(2,1);}  // on      
      }
if(code_rm2_off == code_remote){
      if(select_2==1){bitSet(status_relay_8,1);update_595_8();EEPROM.write(2,0);}   // off
}

if(code_rm3_on == code_remote){   
      if(select_3==0){
      if(bitRead(status_relay_8,2)==1){ bitClear(status_relay_8,2);update_595_8();EEPROM.write(3,1);   //on
                                      } 
      if(bitRead(status_relay_8,2)==0){ bitSet(status_relay_8,2);update_595_8();EEPROM.write(3,0); // off 
                                      }        
      }
rl3:  if(select_3==1){bitClear(status_relay_8,2);update_595_8();EEPROM.write(3,1);}  // on      
      }
if(code_rm3_off == code_remote){
      if(select_3==1){bitSet(status_relay_8,2);update_595_8();EEPROM.write(3,0);}   // off
}

if(code_rm4_on == code_remote){   
      if(select_4==0){
      if(bitRead(status_relay_8,3)==1){ bitClear(status_relay_8,3);update_595_8();EEPROM.write(4,1);   //on
                                        } 
      if(bitRead(status_relay_8,3)==0){ bitSet(status_relay_8,3);update_595_8();EEPROM.write(4,0); // off 
                                      }        
      }
rl4:  if(select_4==1){bitClear(status_relay_8,3);update_595_8();EEPROM.write(4,1);}  // on      
      }
if(code_rm4_off == code_remote){
      if(select_4==1){bitSet(status_relay_8,3);update_595_8();EEPROM.write(4,0);}   // off
}

if(code_rm5_on == code_remote){   
      if(select_5==0){
      if(bitRead(status_relay_8,4)==1){ bitClear(status_relay_8,4);update_595_8();EEPROM.write(5,1);   //on
                                      } 
      if(bitRead(status_relay_8,4)==0){ bitSet(status_relay_8,4);update_595_8();EEPROM.write(5,0); // off 
                                      }        
      }
rl5:  if(select_5==1){bitClear(status_relay_8,4);update_595_8();EEPROM.write(5,1);}  // on      
      }
if(code_rm5_off == code_remote){
      if(select_5==1){bitSet(status_relay_8,4);update_595_8();EEPROM.write(5,0);}   // off
}

if(code_rm6_on == code_remote){   
      if(select_6==0){
      if(bitRead(status_relay_8,5)==1){ bitClear(status_relay_8,5);update_595_8();EEPROM.write(6,1);   //on
                                      } 
      if(bitRead(status_relay_8,5)==0){ bitSet(status_relay_8,5);update_595_8();EEPROM.write(6,0); // off 
                                      }        
      }
rl6:  if(select_6==1){bitClear(status_relay_8,5);update_595_8();EEPROM.write(6,1);}  // on      
      }
if(code_rm6_off == code_remote){
      if(select_6==1){bitSet(status_relay_8,5);update_595_8();EEPROM.write(6,0);}   // off
}

if(code_rm7_on == code_remote){   
      if(select_7==0){
      if(bitRead(status_relay_8,6)==1){ bitClear(status_relay_8,6);update_595_8();EEPROM.write(7,1);   //on
                                        goto rl7;} 
      if(bitRead(status_relay_8,6)==0){ bitSet(status_relay_8,6);update_595_8();EEPROM.write(7,0); // off 
                                        }        
      }
rl7:  if(select_7==1){bitClear(status_relay_8,6);update_595_8();EEPROM.write(7,1);}  // on      
      }
if(code_rm7_off == code_remote){
      if(select_7==1){bitSet(status_relay_8,6);update_595_8();EEPROM.write(7,0);}   // off
}

if(code_rm8_on == code_remote){   
      if(select_8==0){
      if(bitRead(status_relay_8,7)==1){ bitClear(status_relay_8,7);update_595_8();EEPROM.write(8,1);   //on
                                       goto rl8;} 
      if(bitRead(status_relay_8,7)==0){ bitSet(status_relay_8,7);update_595_8();EEPROM.write(8,0); // off 
                                      }        
      }
rl8:  if(select_8==1){bitClear(status_relay_8,7);update_595_8();EEPROM.write(8,1);}  // on      
      }
if(code_rm8_off == code_remote){
      if(select_8==1){bitSet(status_relay_8,7);update_595_8();EEPROM.write(8,0);}   // off
}

if(code_rm9_on == code_remote){   
      if(select_9==0){
      if(bitRead(status_relay_7,1)==1){ bitClear(status_relay_7,1);update_595_7();EEPROM.write(9,1);   //on
                                      goto rl9;} 
      if(bitRead(status_relay_7,1)==0){ bitSet(status_relay_7,1);update_595_7();EEPROM.write(9,0); // off 
                                      }        
      }
rl9:  if(select_9==1){bitClear(status_relay_7,1);update_595_7();EEPROM.write(9,1);}  // on      
      }
if(code_rm9_off == code_remote){
      if(select_9==1){bitSet(status_relay_7,1);update_595_7();EEPROM.write(9,0);}   // off
}

if(code_rm10_on == code_remote){   
      if(select_10==0){
      if(bitRead(status_relay_7,2)==1){ bitClear(status_relay_7,2);update_595_7();EEPROM.write(10,1);   //on
                                        goto rl10;} 
      if(bitRead(status_relay_7,2)==0){ bitSet(status_relay_7,2);update_595_7();EEPROM.write(10,0); // off 
                                      ;}        
      }
rl10:  if(select_10==1){bitClear(status_relay_7,2);update_595_7();EEPROM.write(10,1);}  // on      
      }
if(code_rm10_off == code_remote){
      if(select_10==1){bitSet(status_relay_7,2);update_595_7();EEPROM.write(10,0);}   // off
}

if(code_rm11_on == code_remote){   
      if(select_11==0){
      if(bitRead(status_relay_7,3)==1){ bitClear(status_relay_7,3);update_595_7();EEPROM.write(11,1);   //on
                                      goto rl11;} 
      if(bitRead(status_relay_7,3)==0){ bitSet(status_relay_7,3);update_595_7();EEPROM.write(11,0); // off 
                                      }        
      }
rl11:  if(select_11==1){bitClear(status_relay_7,3);update_595_7();EEPROM.write(11,1);}  // on      
      }
if(code_rm11_off == code_remote){
      if(select_11==1){bitSet(status_relay_7,3);update_595_7();EEPROM.write(11,0);}   // off
}

if(code_rm12_on == code_remote){   
      if(select_12==0){
      if(bitRead(status_relay_7,4)==1){ bitClear(status_relay_7,4);update_595_7();EEPROM.write(12,1);   //on
                                       goto rl12;} 
      if(bitRead(status_relay_7,4)==0){ bitSet(status_relay_7,4);update_595_7();EEPROM.write(12,0); // off 
                                      }        
      }
rl12:  if(select_12==1){bitClear(status_relay_7,4);update_595_7();EEPROM.write(12,1);}  // on      
      }
if(code_rm12_off == code_remote){
      if(select_12==1){bitSet(status_relay_7,4);update_595_7();EEPROM.write(12,0);}   // off
}

if(code_rm13_on == code_remote){   
      if(select_13==0){
      if(bitRead(status_relay_7,5)==1){ bitClear(status_relay_7,5);update_595_7();EEPROM.write(13,1);   //on
                                        goto rl13;} 
      if(bitRead(status_relay_7,5)==0){ bitSet(status_relay_7,5);update_595_7();EEPROM.write(13,0); // off 
                                      }        
      }
rl13:  if(select_13==1){bitClear(status_relay_7,5);update_595_7();EEPROM.write(13,1);}  // on      
      }
if(code_rm13_off == code_remote){
      if(select_13==1){bitSet(status_relay_7,5);update_595_7();EEPROM.write(13,0);}   // off
}

if(code_rm14_on == code_remote){   
      if(select_14==0){
      if(bitRead(status_relay_7,6)==1){ bitClear(status_relay_7,6);update_595_7();EEPROM.write(14,1);   //on
                                      } 
      if(bitRead(status_relay_7,6)==0){ bitSet(status_relay_7,6);update_595_7();EEPROM.write(14,0); // off 
                                      }        
      }
rl14:  if(select_14==1){bitClear(status_relay_7,6);update_595_7();EEPROM.write(14,1);}  // on      
      }
if(code_rm14_off == code_remote){
      if(select_14==1){bitSet(status_relay_7,6);update_595_7();EEPROM.write(14,0);}   // off
}

if(code_rm15_on == code_remote){   
      if(select_15==0){
      if(bitRead(status_relay_7,7)==1){ bitClear(status_relay_7,7);update_595_7();EEPROM.write(15,1);   //on
                                       goto rl15;} 
      if(bitRead(status_relay_7,7)==0){ bitSet(status_relay_7,7);update_595_7();EEPROM.write(15,0); // off 
                                      }        
      }
rl15:  if(select_15==1){bitClear(status_relay_7,7);update_595_7();EEPROM.write(15,1);}  // on      
      }
if(code_rm15_off == code_remote){
      if(select_15==1){bitSet(status_relay_7,7);update_595_7();EEPROM.write(15,0);}   // off
}

    EEPROM.commit();
    //delay(100);
    read_eeprom();
    reard_eeprom_rm();
    
}


//=======================================================
void handleRoot() {
  int n = WiFi.scanNetworks();  // Quét các mạng Wi-Fi xung quanh
  String html = R"=====(
    <html>
      <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
          body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            background-color: #f7f7f7;
            color: #333;
          }
          .container {
            width: 90%;
            max-width: 400px;
            padding: 20px;
            background-color: white;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
          }
          h1 {
            font-size: 24px;
            margin-bottom: 20px;
            text-align: center;
            color: #007bff;
          }
          label {
            display: block;
            margin-bottom: 8px;
            font-weight: bold;
            color: #555;
          }
          select, input[type="text"], input[type="submit"] {
            width: 100%;
            padding: 10px;
            margin-bottom: 20px;
            border: 1px solid #ccc;
            border-radius: 4px;
            font-size: 16px;
            box-sizing: border-box;
          }
          input[type="submit"] {
            background-color: #007bff;
            color: white;
            border: none;
            cursor: pointer;
            transition: background-color 0.3s;
          }
          input[type="submit"]:hover {
            background-color: #0056b3;
          }
          @media (prefers-color-scheme: dark) {
            body {
              background-color: #333;
              color: #f7f7f7;
            }
            .container {
              background-color: #444;
              box-shadow: 0 0 10px rgba(255, 255, 255, 0.1);
            }
            input[type="text"], select {
              background-color: #555;
              border: 1px solid #666;
              color: #f7f7f7;
            }
            input[type="submit"] {
              background-color: #1a73e8;
            }
            input[type="submit"]:hover {
              background-color: #0056b3;
            }
          }
        </style>
      </head>
      <body>
        <div class="container">
          <h1>Setup WIFI</h1>
          <form action="/submit" method="post">
            <label for="ssid">SSID</label>
            <select name="ssid" id="ssid">
  )=====";
  for (int i = 0; i < n; ++i) {
    html += "<option value=\"" + WiFi.SSID(i) + "\">" + WiFi.SSID(i) + " (" + String(WiFi.RSSI(i)) + " dBm)</option>";
  }
  html += R"=====(
            </select>
            <label for="password">Password</label>
            <input type="text" name="password" id="password">
            <label for="server_ip">Server IP</label>
            <input type="text" name="server_ip" id="server_ip">
            <label for="subscribe_topic">Subscribe Topic</label>
            <input type="text" name="subscribe_topic" id="subscribe_topic">
            <label for="publish_topic">Publish Topic</label>
            <input type="text" name="publish_topic" id="publish_topic">
            <label for="name_device">Device Name</label>
            <input type="text" name="name_device" id="name_device">
            <input type="submit" value="Submit">
          </form>
        </div>
      </body>
    </html>
  )=====";
  server.send(200, "text/html", html);
}
//========================================================
void reset_name_wifi(){
  for (int i = 500; i <= 599; ++i) {
          EEPROM.write(i, 0);  // Xoa eepromm
          }
  EEPROM.commit();
  read_eeprom_system();
  ESP.restart();        
}

//=========================================================
void handleSubmit() {
  Wifi_ssid = server.arg("ssid");
  Wifi_password = server.arg("password");
  Server_ip = server.arg("server_ip");
  Subscribe_topic = server.arg("subscribe_topic");
  Publish_topic = server.arg("publish_topic");
  Name_device = server.arg("name_device");

  if (Wifi_ssid.length() > 0) { 
      for (int i = 500; i <= 549; ++i) {
          EEPROM.write(i, 0);  // Xoa eepromm
          }
      Serial.println("");
      Serial.println("writing eeprom wifi name :");  
      for (int i = 0; i < Wifi_ssid.length(); ++i){     // Ghi name Wifi
          EEPROM.write(500 + i, Wifi_ssid[i]);
          Serial.print("Wrote: ");
          Serial.println(Wifi_ssid[i]);
        } 
  }

  if (Wifi_password.length() > 0) { 
      for (int i = 550; i <= 599; ++i) {
            EEPROM.write(i, 0);  // Xoa eepromm
          }
      Serial.println("");
      Serial.println("writing eeprom pass wifi :"); 
  
      for (int i = 0; i < Wifi_password.length(); ++i){     // Ghi Wifi pass
          EEPROM.write(550 + i, Wifi_password[i]);
          Serial.print("Wrote: ");
          Serial.println(Wifi_password[i]);
        }
  }

  if (Server_ip.length() > 0) { 
      for (int i = 600; i <= 619; ++i) {
            EEPROM.write(i, 0);  // Xoa eepromm
          }
      for (int i = 0; i < Server_ip.length(); ++i){     // Ghi Wifi pass
          EEPROM.write(600 + i, Server_ip[i]);
          Serial.print("Wrote: ");
          Serial.println(Server_ip[i]);
        }    
  }
  
  if (Subscribe_topic.length() > 0) { 
      for (int i = 620; i <= 639; ++i) {
            EEPROM.write(i, 0);  // Xoa eepromm
          }
      for (int i = 0; i < Subscribe_topic.length(); ++i){     // Ghi Wifi pass
          EEPROM.write(620 + i, Subscribe_topic[i]);
          Serial.print("Wrote: ");
          Serial.println(Subscribe_topic[i]);
        }
  }
  if (Publish_topic.length() > 0) { 
      for (int i = 640; i <= 659; ++i) {
            EEPROM.write(i, 0);  // Xoa eepromm
          }
      for (int i = 0; i < Publish_topic.length(); ++i){     // Ghi Wifi pass
          EEPROM.write(640 + i, Publish_topic[i]);
          Serial.print("Wrote: ");
          Serial.println(Publish_topic[i]);
        }
  }

  if (Name_device.length() > 0) { 
      for (int i = 660; i <= 679; ++i) {
            EEPROM.write(i, 0);  // Xoa eepromm
          }
      for (int i = 0; i < Name_device.length(); ++i){     // Ghi Wifi pass
          EEPROM.write(660 + i, Name_device[i]);
          Serial.print("Wrote: ");
          Serial.println(Name_device[i]);
        }
  }

  EEPROM.commit();
  read_eeprom_system();

  //Serial.println("Received SSID: " + Wifi_ssid);
  //Serial.println("Received Password: " + Wifi_password);
  //Serial.println("Received Server IP: " + Server_ip);
  //Serial.println("Received Subscribe Topic: " + Subscribe_topic);
  //Serial.println("Received Publish Topic: " + Publish_topic);
  //Serial.println("Received Device Name: " + Name_device);

  // Lưu thông tin Wi-Fi, server IP, subscribe topic, publish topic và tên thiết bị, có thể lưu vào EEPROM nếu cần

  server.send(200, "text/html", "<html><body><h1>Settings Saved! Rebooting...</h1></body></html>");

  delay(2000);
  ESP.restart();
}
//===============================================
void read_eeprom_system(){
  Wifi_ssid = "";
  Wifi_password = "";
  Server_ip = "";
  Subscribe_topic = "";
  Publish_topic = "";
  Name_device = "";
  
    // read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");
  for (int i = 500; i < 549; ++i)
  {
    Wifi_ssid += char(EEPROM.read(i));
  }
  Serial.print("WiFi Name: ");
  
  Serial.println(Wifi_ssid);
  for (int i = 550; i < 599; ++i)
  {
    Wifi_password += char(EEPROM.read(i));
  }
  Serial.print("Pass: ");
  Serial.println(Wifi_password);
 
  for (int i = 600; i < 619; ++i)
    {
      Server_ip += char(EEPROM.read(i));
    }
    Serial.print("Server-IP: ");
    mqtt_server = Server_ip.c_str();          // string to const char* arduino
    Serial.println(mqtt_server); 
    
    
  for (int i = 620; i < 639; ++i)
    {
      Subscribe_topic += char(EEPROM.read(i));
    }
    Serial.print("Subscribe_topic: ");
    subscribe_topic = Subscribe_topic.c_str();          // string to const char* arduino
    Serial.println(subscribe_topic);
    
    
  for (int i = 640; i < 659; ++i)
    {
      Publish_topic += char(EEPROM.read(i));
    }
    Serial.print("Publish_topic: ");
    publish_topic = Publish_topic.c_str();          // string to const char* arduino
    Serial.println(publish_topic);
    
  for (int i = 660; i < 679; ++i)
    {
      Name_device += char(EEPROM.read(i));
    }
    Serial.print("Name_device: ");
    name_device = Name_device.c_str();          // string to const char* arduino
    Serial.println(name_device);  
}
