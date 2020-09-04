/* 
Date  : 19/08/2020
Author: DungTT
To handle core tasks: Send/receive HTTP request, parse string, display
This project is just considered about stable of device!
Including: 
Connect to server
Send request
Receive request
Parse data
Display data
 */
#include "main.h"
#include <ArduinoJson.h>

#define _DEBUG_ 1
#define IS_BUTTON_PRESS LOW
const uint8_t QRcode[] = {0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,0XFF,0XF8,0X7C,0X00,0X30,
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
const char* curr = "VND";
static msg_server_pack msg_server;
/* =========================================RUN MODE============================================ */
/*
@date : 19/08/2020
@brief: parse json packet from server
@para :
@return: none
 */
bool parse_data_wifi(String json) {
    DynamicJsonDocument doc(1024);
    // char* json;
    DeserializationError error = deserializeJson(doc, json); 

    if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        
        msg_server.is_parse_ok = false;
        return false;
        // exit(0);
    }
    /* client_response.flush();
    client_response.print("OK"); */
    
    msg_server.status_connect = doc["msg"].as<String>();
    msg_server.item = doc["name"].as<String>();
    msg_server.price = doc["price"].as<String>();

    #if _DEBUG_
        Serial.println("Parsing json:");
        Serial.println(msg_server.status_connect);
        Serial.println(msg_server.item);
        Serial.println(msg_server.price);
    #endif

    return true;
}

/*
@date : 19/08/2020
@brief: send request to server
@para : host, port
@return: none
 */
String Send_Request_to_Server()
{
    const char* host = Load_Server_Address();
    int httpPort = Load_Server_Port();

    #ifdef _DEBUG_
        Serial.print("connecting to ");
        Serial.println(host);
    #endif

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    if (!client.connect(host, httpPort)) {
        #if _DEBUG_
        Serial.println("Connect Server failed!");
        #endif
        return "Connect Server failed!";
    }

    // We now create a URI for the request
    String url = "/api/device/";
    url += WiFi.macAddress();
    url += "/product";

    #if _DEBUG_
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
            return "Client Timeout";
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    String resp = "{";
    while (client.available()) {
        String header = client.readStringUntil('{');//to clear buffer
        resp += client.readStringUntil('}') + "}";
        client.flush();

        #if _DEBUG_
            Serial.println("Data receive from server:");
            Serial.println(header);
            Serial.println(resp);
        #endif
    }
    
    client.flush();
    client.print("OK");
    return resp;
    // parse_data(client, line);
}

/*
@date : 26/08/2020
@brief: handle run mode: send request to server, read json string, display
@para : none
@return: none
*/
int Run_Mode_Handle(){
    #if _DEBUG_
        Serial.println("Run Mode:");
    #endif
    String httpRespond;
    
    // Epaper_Init();
    if (Wifi_Connect()){//WiFi failed
        httpRespond = Send_Request_to_Server();
        #if _DEBUG_
            Serial.println("Connect WiFi ok!");
            Serial.println(httpRespond);
        #endif
    }
    else{//WiFi ok
        Epaper_Display_Error("Cannot connect to WIFI");
        Serial.println("Can not connect WiFi!");
        goToDeepSleep(TIME_WAKE_UP_INTERVAL_ERROR);//Try another one
        return -1;
    }

    if (httpRespond != "{}"){//data feedback ok
        if (parse_data_wifi(httpRespond)){//parse data ok
            #if _DEBUG_
                Serial.println("Parse json ok");
                Serial.println(msg_server.status_connect);
                Serial.println(msg_server.item);
                Serial.println(msg_server.price);
            #endif
            display_price(msg_server.item, msg_server.price, curr, QRcode);
        }
        else{//parse data failed
            #if _DEBUG_
            Serial.println("Parse json failed!");
            Epaper_Display_Error("Format data failed!");
            goToDeepSleep(TIME_WAKE_UP_INTERVAL_ERROR);
            #endif
        }   
    }
    else{//data feedback failed
        #if _DEBUG_
            Serial.print("BAD data received: ");
            Serial.println(httpRespond);
            Epaper_Display_Error("Get data failed!");
            goToDeepSleep(TIME_WAKE_UP_INTERVAL_ERROR);
        #endif
    }
    goToDeepSleep(TIME_WAKE_UP_INTERVAL_NORMAL);
}

/* =========================================CONFIG MODE============================================ */

/*
@date : 25/08/2020
@brief: check if Button Config Mode is pressed
@para : timeout in ms
@return: true/false
 */
bool Check_Config_Mode(unsigned long timeout){
    if (digitalRead(BUTTON_PIN) == IS_BUTTON_PRESS){
        #if _DEBUG_
            Serial.println("BUTTON PIN is pressed");
        #endif
        for (int i=0; i<(timeout/500); i++){
            if (digitalRead(BUTTON_PIN) != IS_BUTTON_PRESS){
                #if _DEBUG_
                    Serial.println("BUTTON PIN debounce");
                #endif
                return false;
            }
            else{
                delay(500);
            }
        }
        #if _DEBUG_
            Serial.println("Config Mode");
        #endif
        Epaper_Display_Config_Mode();
        return true;
    }    
    return false;
}

/*
@date : 26/08/2020
@brief: handle config mode: read data from BLT (json) -> write into EEPROM
@para : none
@return: none
*/
int Config_Mode_Handle(){
    Bluetooth_Init();

    while (!SerialBT.available()){};

    String incomming_data = "";
    
    if (Bluetooth_Read_String('\n', incomming_data)){
        Config_Data_WiFi(incomming_data);
    }
    Epaper_Display_Config_Done();
    return 1;
}

/* =========================================TASK MANAGER============================================ */
/*
@date : 25/08/2020
@brief: check if Button Config Mode is pressed
@para : timeout in ms
@return: true/false
 */
int Core_Task_Init(){
    if (Check_Config_Mode(TIME_CHECK_BUTTON_PRESS)){
        Config_Mode_Handle();
    }
    else{
        Run_Mode_Handle();
    }
}



