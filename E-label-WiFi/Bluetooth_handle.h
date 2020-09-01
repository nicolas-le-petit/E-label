#ifndef  _BLUETOOTH_HANDLE_H
#define _BLUETOOTH_HANDLE_H
#endif

/* #ifdef __cplusplus
extern "C" {
#endif */

#include "BluetoothSerial.h"
#include "Arduino.h"
#include <WiFi.h>//to get MAC

extern BluetoothSerial SerialBT;

// #define BLUETOOTH_NAME "HNN_Device"

void Bluetooth_Init();
bool Bluetooth_Read_String(char terminator, String& inStr);
void Bluetooth_Write(String msg);
String getMacAddress();
