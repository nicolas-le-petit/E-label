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

/*
@date : 19/08/2020
@brief: parse json packet from server
@para :
@return: none
 */
bool parse_data(WiFiClient client_response, String json) {
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

    return true;
}

bool Send_Request_to_Server(const char* host, int httpPort)
{
    host = "192.168.99.108";
    httpPort = 80;
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

/*
@date : 19/08/2020
@brief: load string of Server IP
@para : none
@return: Ip
 */
const char* Load_Server_Address(){
    String load_data = Read_EEPROM(IP_SERVER_ADDRESS, IP_SERVER_BUFFER_MAX);
    // return load_data;
    const char* Server_Address;
    Server_Address = load_data.c_str();
    return Server_Address;
}

/*
@date : 19/08/2020
@brief: load httpport
@para : none
@return: port
 */
int Load_Server_Port(){
    String load_data = Read_EEPROM(SERVER_PORT_ADDRESS, SERVER_PORT_BUFFER_MAX); 
    int server_port = load_data.toInt();
    return server_port;
}