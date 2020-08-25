// include library, include base class, make path known
#include <GxEPD.h>
#include "SD.h"
#include "SPI.h"

#include "WiFi.h" 
#include "driver/adc.h"
#include <esp_wifi.h>
#include <esp_bt.h>
#include <ArduinoJson.h>

#define DEEP_SLEEP_TIME 0.5
#define NUM_SAMPLES 10
#define BATTERY_METTER_PIN 35
#define BASE_TIME_US 1000000 // base time in us
#define BASE_TIME_MINUTE 60 //60s in a minute

//! There are three versions of the 2.13 screen,
//  if you are not sure which version, please test each one,
//  if it is successful then it belongs to the model of the file name

//#include <GxGDE0213B1/GxGDE0213B1.h>      // 2.13" b/w
#include <GxGDEH0213B72/GxGDEH0213B72.h>  // 2.13" b/w new panel
//#include <GxGDEH0213B73/GxGDEH0213B73.h>  // 2.13" b/w newer panel

// int bmpWidth = 120, bmpHeight = 120;
//width:150,height:39
const unsigned char image[] = { /* 0X00,0X01,0X4B,0X00,0X4C,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,0XFF,0XF8,0X7C,0X00,0X30,
0XC7,0XFF,0XFF,0X80,0X7F,0XFF,0XFC,0XFC,0X00,0X39,0XC7,0XFF,0XFF,0X80,0X7F,0XFF,
0XFC,0XFC,0X00,0X39,0XC7,0XFF,0XFF,0X80,0X70,0X00,0X1C,0X00,0X01,0XC0,0X07,0X00,
0X03,0X80,0X70,0X00,0X1C,0X00,0X01,0XC0,0X07,0X00,0X03,0X80,0X70,0X00,0X1C,0X00,
0X01,0XC0,0X07,0X00,0X03,0X80,0X71,0XFF,0X1C,0XE0,0X7F,0XC6,0X07,0X1F,0XF3,0X80,
0X71,0XFF,0X1C,0XE0,0X7F,0XC6,0X07,0X1F,0XF3,0X80,0X71,0XFF,0X1C,0XE0,0X7F,0XC6,
0X07,0X1F,0XF3,0X80,0X71,0XFF,0X1C,0XFC,0X71,0XF8,0X07,0X1F,0XF3,0X80,0X71,0XFF,
0X1C,0XFC,0X71,0XF8,0X07,0X1F,0XF3,0X80,0X71,0XFF,0X1C,0XFC,0X71,0XF8,0X07,0X1F,
0XF3,0X80,0X71,0XFF,0X1C,0XFF,0XF1,0XFE,0X07,0X1F,0XF3,0X80,0X71,0XFF,0X1C,0XFF,
0XF1,0XFE,0X07,0X1F,0XF3,0X80,0X71,0XFF,0X1C,0XFF,0XF1,0XFE,0X07,0X1F,0XF3,0X80,
0X70,0X00,0X1C,0X1C,0X0E,0X39,0XC7,0X00,0X03,0X80,0X70,0X00,0X1C,0X1C,0X0E,0X39,
0XC7,0X00,0X03,0X80,0X70,0X00,0X1C,0X1C,0X0E,0X39,0XC7,0X00,0X03,0X80,0X7F,0XFF,
0XFC,0XE3,0X8E,0X39,0XC7,0XFF,0XFF,0X80,0X7F,0XFF,0XFC,0XE3,0X8E,0X39,0XC7,0XFF,
0XFF,0X80,0X7F,0XFF,0XFC,0XE3,0X8E,0X39,0XC7,0XFF,0XFF,0X80,0X00,0X00,0X00,0X1C,
0X70,0X39,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X1C,0X70,0X39,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X1C,0X70,0X39,0XC0,0X00,0X00,0X00,0X7F,0XF8,0X1C,0XE0,0X00,0X00,
0X38,0X1F,0XF3,0X80,0X7F,0XF8,0X1C,0XE0,0X00,0X00,0X38,0X1F,0XF3,0X80,0X7F,0XF8,
0X1C,0XE0,0X00,0X00,0X38,0X1F,0XF3,0X80,0X70,0X3F,0X00,0XFC,0X01,0XC1,0XC0,0XE0,
0X0C,0X00,0X70,0X3F,0X00,0XFC,0X01,0XC1,0XC0,0XE0,0X0C,0X00,0X70,0X3F,0X00,0XFC,
0X01,0XC1,0XC0,0XE0,0X0C,0X00,0X70,0X07,0X1C,0XE0,0X01,0XC1,0XC7,0X1C,0X00,0X00,
0X70,0X07,0X1C,0XE0,0X01,0XC1,0XC7,0X1C,0X00,0X00,0X70,0X07,0X00,0XE0,0X7F,0XF8,
0X3F,0XFF,0XF0,0X00,0X70,0X07,0X00,0XE0,0X7F,0XF8,0X3F,0XFF,0XF0,0X00,0X70,0X07,
0X00,0XE0,0X7F,0XF8,0X3F,0XFF,0XF0,0X00,0X0E,0X38,0X1F,0XFC,0X70,0X06,0X3F,0X1C,
0X7F,0X80,0X0E,0X38,0X1F,0XFC,0X70,0X06,0X3F,0X1C,0X7F,0X80,0X0E,0X38,0X1F,0XFC,
0X70,0X06,0X3F,0X1C,0X7F,0X80,0X01,0XC0,0X03,0X03,0XF1,0XFF,0XFF,0XFC,0X03,0X80,
0X01,0XC0,0X03,0X03,0XF1,0XFF,0XFF,0XFC,0X03,0X80,0X01,0XC0,0X03,0X03,0XF1,0XFF,
0XFF,0XFC,0X03,0X80,0X0E,0X07,0XFF,0XFC,0X0E,0X39,0XFF,0X1C,0X7C,0X00,0X0E,0X07,
0XFF,0XFC,0X0E,0X39,0XFF,0X1C,0X7C,0X00,0X0E,0X07,0XFF,0XFC,0X0E,0X39,0XFF,0X1C,
0X7C,0X00,0X71,0XF8,0XE3,0X1F,0X8F,0XC1,0XC0,0XFC,0X03,0X80,0X71,0XF8,0XE3,0X1F,
0X8F,0XC1,0XC0,0XFC,0X03,0X80,0X71,0XF8,0XE3,0X1F,0X8F,0XC1,0XC0,0XFC,0X03,0X80,
0X01,0XFF,0X1C,0XFC,0X70,0X07,0XFF,0XFF,0XFF,0X80,0X01,0XFF,0X1C,0XFC,0X70,0X07,
0XFF,0XFF,0XFF,0X80,0X01,0XFF,0X1C,0XFC,0X70,0X07,0XFF,0XFF,0XFF,0X80,0X00,0X00,
0X00,0XFC,0X0F,0XC1,0XC0,0X1C,0X73,0X80,0X00,0X00,0X00,0XFC,0X0F,0XC1,0XC0,0X1C,
0X73,0X80,0X00,0X00,0X00,0XFC,0X0F,0XC1,0XC0,0X1C,0X73,0X80,0X7F,0XFF,0XFC,0X1F,
0XFE,0X01,0XC7,0X1C,0X7F,0X80,0X7F,0XFF,0XFC,0X1F,0XFE,0X01,0XC7,0X1C,0X7F,0X80,
0X7F,0XFF,0XFC,0X1F,0XFE,0X01,0XC7,0X1C,0X7F,0X80,0X70,0X00,0X1C,0X03,0X8E,0X07,
0XC0,0X1C,0X0C,0X00,0X70,0X00,0X1C,0X03,0X8E,0X07,0XC0,0X1C,0X0C,0X00,0X70,0X00,
0X1C,0X03,0X8E,0X07,0XC0,0X1C,0X0C,0X00,0X71,0XFF,0X1C,0X00,0X7F,0XC1,0XFF,0XFF,
0X8C,0X00,0X71,0XFF,0X1C,0X00,0X7F,0XC1,0XFF,0XFF,0X8C,0X00,0X71,0XFF,0X1C,0XE3,
0X8F,0XF8,0X3F,0X1F,0XFF,0X80,0X71,0XFF,0X1C,0XE3,0X8F,0XF8,0X3F,0X1F,0XFF,0X80,
0X71,0XFF,0X1C,0XE3,0X8F,0XF8,0X3F,0X1F,0XFF,0X80,0X71,0XFF,0X1C,0XFF,0XFF,0XC1,
0XFF,0X1C,0X7C,0X00,0X71,0XFF,0X1C,0XFF,0XFF,0XC1,0XFF,0X1C,0X7C,0X00,0X71,0XFF,
0X1C,0XFF,0XFF,0XC1,0XFF,0X1C,0X7C,0X00,0X70,0X00,0X1C,0XE0,0X00,0X06,0X38,0X1C,
0X70,0X00,0X70,0X00,0X1C,0XE0,0X00,0X06,0X38,0X1C,0X70,0X00,0X70,0X00,0X1C,0XE0,
0X00,0X06,0X38,0X1C,0X70,0X00,0X7F,0XFF,0XFC,0XFC,0X0E,0X38,0X3F,0XFF,0XFF,0X80,
0X7F,0XFF,0XFC,0XFC,0X0E,0X38,0X3F,0XFF,0XFF,0X80,0X7F,0XFF,0XFC,0XFC,0X0E,0X38,
0X3F,0XFF,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,};

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <Fonts/Tiny3x3a2pt7b.h>


#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#define SPI_MOSI 23
#define SPI_MISO -1
#define SPI_CLK 18

#define ELINK_SS 5
#define ELINK_BUSY 4
#define ELINK_RESET 16
#define ELINK_DC 17

#define SDCARD_SS 13
#define SDCARD_CLK 14
#define SDCARD_MOSI 15
#define SDCARD_MISO 2

#define BUTTON_PIN 39


GxIO_Class io(SPI, /*CS=5*/ ELINK_SS, /*DC=*/ ELINK_DC, /*RST=*/ ELINK_RESET);
GxEPD_Class display(io, /*RST=*/ ELINK_RESET, /*BUSY=*/ ELINK_BUSY);

SPIClass sdSPI(VSPI);

RTC_DATA_ATTR int bootCount = 0;
const char* ssid = "HNN_IoT";
const char* password = "honeynet.vn";

String g_status_connect;
String g_item;
String g_price;

/* char* status_connect;
char* item;
char* price; */

#define _DEBUG_ 1

/*
@date : 19/08/2020
@brief: parse json packet from server
@para :
@return: none
 */
bool parse_data(WiFiClient client_response, String json) {
    //  StaticJsonBuffer<1880> jsonBuffer;
    // DynamicJsonDocument jsonBuffer(1024);

    // JsonObject root_data = jsonBuffer.parseObject(data);
    // DeserializationError error = deserializeJson(jsonBuffer, root_data);
    DynamicJsonDocument doc(1024);
    // char* json;
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        return false;
    }
    client_response.flush();
    client_response.print("OK");

    String status_connect = doc["msg"];
    String item = doc["name"];
    String price = doc["price"];
    /* String note = doc["Note"];
    unsigned char image = doc["QR code"] */;
    g_item = item;
    g_price = price;
    return true;
}

/*
@date : 19/08/2020
@brief: send request to server
@para : host & port
@return: none
 */
bool Send_Request_to_Server()
{
    const char* host = "192.168.99.108";
    int httpPort = 80;
    #ifdef _DEBUG_
        Serial.print("connecting to ");
        Serial.println(host);
    #endif

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return false;
    }

    // We now create a URI for the request
    String url = "/api/device/";
    url += WiFi.macAddress();
    url += "/product";

    #ifdef _DEBUG_
        Serial.print("Requesting URL: ");
        Serial.println(url);
    #endif

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n\r\n" );
                // "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return false;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    String line = "{";
    while (client.available()) {
        String line_del = client.readStringUntil('{');//to clear buffer
        line += client.readStringUntil('}') + "}";
        client.flush();
    }
    parse_data(client, line);
}

void Epaper_init(){
    SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, ELINK_SS);
    display.init(); // enable diagnostic output on Serial

    display.setRotation(1);
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(0, 0);
}

void Wifi_Connect(const char * & ssid, const char * & password) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    for (int i=0; i<30; i++){
      if (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      else{
        break;
      }
    }

    // Make sure that we're actually connected, otherwise go to deep sleep
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("FAILED");
        //goToDeepSleep();
    }
    #if 1
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    #endif
}

void display_price(){
    display.drawBitmap(image, display.width()/2 + 50, display.height()/4 + 15,  76, 76, GxEPD_BLACK);

    display.setCursor(0, 18);
    display.println(g_item);

    display.setCursor(display.width(), 18+30);
    display.setFont(&FreeMonoBold9pt7b);

    display.setFont(&FreeMonoBold18pt7b);
    display.println(g_price);
    display.println("VND");

    display.update();
}

void board_GotoSleep(){
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    btStop();

    // adc_power_off();//keep pin 35 awake for capacity measurement
    esp_wifi_stop();
    esp_bt_controller_disable();

    esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME * BASE_TIME_MINUTE * BASE_TIME_US);
    //esp_sleep_enable_ext0_wakeup(GPIO_NUM_39, level);

    esp_deep_sleep_start();
}

bool check_config_mode(){
    if (digitalRead(BUTTON_PIN) == LOW){
        delay(2000);
        if (digitalRead(BUTTON_PIN) == LOW){
            display.println("Config mode");
            return true;
        }      
    }
    return false;
}

void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println("Ready!");
    pinMode(BUTTON_PIN, OUTPUT);

    Epaper_init();
    Wifi_Connect(ssid,password);
    Send_Request_to_Server();

    display_price();
    board_GotoSleep();
    
    Serial.println("Going to sleep now");
}

void loop()
{
    // get_Batery_Value();
    // delay(15000);
}

//#define NUM_SAMPLES 9
int get_Batery_Value() {
    int sample_count = 0;
    int sum = 0;
   
    while (sample_count < NUM_SAMPLES) {
        sum += analogRead(BATTERY_METTER_PIN);
        // Serial.println(sum);
        sample_count++;
        delay(10);
    }

    float voltage = (sum/NUM_SAMPLES)/ 2350.0;
    int batteryLevel = _min(map(sum / NUM_SAMPLES, 2000, 2440, 0, 100), 100); //1100
    if (sum/NUM_SAMPLES < 1200) batteryLevel = 0;
    /* Serial.print("Valor Analogo: ");
    Serial.println(sum);
    Serial.print("Battery Lavel:");
    Serial.print(batteryLevel);
    Serial.println("%"); */
    sample_count = 0; //Reset counter
    sum = 0; //Reset counter
    voltage = voltage * 4.20;
    /* Serial.print(voltage);
    Serial.println (" V"); */
    //batteryLevel *= 100;
    //batteryLevel = (int)(batteryLevel);
    display.setCursor(0, 12);
    display.setFont(&FreeMonoBold9pt7b);
    //display.setFont(&Tiny3x3a2pt7b);    
    display.print(batteryLevel);
    display.print("%");
    // display.update();
}
