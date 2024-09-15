#include <SimpleTimer.h>

int code_remote=0;
int del=0;
String data_rf="";
int k,m=0,count_tke=0;
bool learning_remote = false;
int learning_relay=0;
int coppy_L1=0;
int read_loop = 0;
int check_code = 12345678;
int con_wifi = 0;


//const char* mqtt_server = "192.168.0.36";
const char* mqtt_server = "";   //string to const char* arduino
const char* name_device = "";
const char* subscribe_topic = "";
const char* publish_topic = "";

WiFiClient espClient;
PubSubClient client(espClient);
// Các topic sử dụng

hw_timer_t *My_timer = NULL;
#define RF_RECEIVER  35
RCSwitch mySwitch = RCSwitch();
SimpleTimer Timer;


String Wifi_ssid;
String Wifi_password;
String Server_ip;
String Subscribe_topic;
String Publish_topic;
String Name_device;

static uint8_t gpio_reset   = 0;

#define latchPin_8  27
#define clockPin_8  26
#define dataPin_8  25

#define latchPin_7  5
#define clockPin_7  4
#define dataPin_7  18


byte status_relay_8 = 255;
byte status_relay_7 = 255;
byte register_8 =255;
byte register_7 =255;

int OE7 = 33;
int OE8 = 32;

static uint8_t SwitchPin1 = 23;  
static uint8_t SwitchPin2 = 22;  
static uint8_t SwitchPin3 = 21; 
static uint8_t SwitchPin4 = 19;  

const char* textOn_relay1 = "mở đèn số 1";
const char* textOff_relay1 = "tắt đèn số 1";
const char* textOn_relay2 = "mở đèn số 2";
const char* textOff_relay2 = "tắt đèn số 2";
const char* textOn_relay3 = "mở đèn số 3";
const char* textOff_relay3 = "tắt đèn số 3";
const char* textOn_relay4 = "mở đèn số 4";
const char* textOff_relay4 = "tắt đèn số 4";
const char* textOn_relay5 = "mở đèn số 5";
const char* textOff_relay5 = "tắt đèn số 5";
const char* textOn_relay6 = "mở đèn số 6";
const char* textOff_relay6 = "tắt đèn số 6";
const char* textOn_relay7 = "mở đèn số 7";
const char* textOff_relay7 = "tắt đèn số 7";
const char* textOn_relay8 = "mở đèn số 8";
const char* textOff_relay8 = "tắt đèn số 8";
const char* textOn_relay9 = "mở đèn số 9";
const char* textOff_relay9 = "tắt đèn số 9";
const char* textOn_relay10 = "mở đèn số 10";
const char* textOff_relay10 = "tắt đèn số 10";
const char* textOn_relay11 = "mở đèn số 11";
const char* textOff_relay11 = "tắt đèn số 11";
const char* textOn_relay12 = "mở đèn số 12";
const char* textOff_relay12 = "tắt đèn số 12";
const char* textOn_relay13 = "mở đèn số 13";
const char* textOff_relay13 = "tắt đèn số 13";
const char* textOn_relay14 = "mở đèn số 14";
const char* textOff_relay14 = "tắt đèn số 14";
const char* textOn_relay15 = "mở đèn số 15";
const char* textOff_relay15 = "tắt đèn số 15";

const char* textOn_all = "mở tất cả đèn";
const char* textOn_all2 = "mở tất cả các đèn";
const char* textOff_all = "tắt tất cả đèn";
const char* textOff_all2 = "tắt tất cả các đèn";



bool check_rl1=LOW,check_rl2=LOW,check_rl3=LOW,check_rl4=LOW,check_rl5=LOW,check_rl6=LOW,check_rl7=LOW,check_rl8=LOW,check_rl9=LOW;
bool check_rl10=LOW,check_rl11=LOW,check_rl12=LOW,check_rl13=LOW,check_rl14=LOW,check_rl15=LOW,check_rl16=LOW;

bool button_on = 1;
bool button_off = 0;

long int code_rm1_on,code_rm2_on,code_rm3_on,code_rm4_on,code_rm5_on,code_rm6_on,code_rm7_on,code_rm8_on;
long int code_rm9_on,code_rm10_on,code_rm11_on,code_rm12_on,code_rm13_on,code_rm14_on,code_rm15_on;
long int code_rm1_off,code_rm2_off,code_rm3_off,code_rm4_off,code_rm5_off,code_rm6_off,code_rm7_off,code_rm8_off;
long int code_rm9_off,code_rm10_off,code_rm11_off,code_rm12_off,code_rm13_off,code_rm14_off,code_rm15_off;
int select_1,select_2,select_3,select_4,select_5,select_6,select_7,select_8,select_9,select_10,select_11,select_12,select_13,select_14,select_15;
