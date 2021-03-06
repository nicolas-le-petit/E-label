//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial
/*
@Date: 21/08/2020
@Autor: DungTT
To handle bluetooth function, including: config

Display name is MAC ID
 */
#include <stdio.h>
#include "Bluetooth_handle.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

/*
@date : 14/08/2020
@brief: get MAC & convert to string
@para :
@return: MAC ID
 */
static String getMacAddress() {
    byte mac[6];
    WiFi.macAddress(mac);
    String cMac = "";
    for (int i = 0; i < 6; ++i) {
        if (mac[i] < 0x10) {
            cMac += "0";
        }
        cMac += String(mac[i], HEX);
        if (i < 5)
            cMac += ":"; // put : or - if you want byte delimiters
        }
    cMac.toUpperCase();
    return cMac;
}

/*
@date : 21/08/2020
@brief: init Bluetooth named by MACID
@para : none
@return: none
 */
void Bluetooth_Init(){
    String BLT_name = getMacAddress();//
    SerialBT.begin(BLT_name);
}

/*
@date : 21/08/2020
@brief: disconnect & end BLT
@para : none
@return: none
 */
void Bluetooth_End(){
    SerialBT.disconnect();
    SerialBT.end();
}

/*
@date : 21/08/2020
@brief: BLT transmit
@para : char array to transmit & its size
@return: none
 */
void Bluetooth_Write(uint8_t* outStr, int size){
    /* const uint8_t * outStr = msg.c_str();
    int size = msg.length(); */
    SerialBT.write(outStr, size);
}

/*
@date : 21/08/2020
@brief: read data from BLT
@para : none
@return: pass-by-refference out string
 */
void Bluetooth_Read_String(String& outStr){
    String inStr;
    // int sizeStr;

    while (!SerialBT.available()){};//wait for Serial available
    
    inStr += SerialBT.readStringUntil('\n');
    // sizeStr++;

    SerialBT.flush();

    /* for (int i = 0; i < sizeStr; i++) { 
          outStr += inStr[i]; 
      } */
}


