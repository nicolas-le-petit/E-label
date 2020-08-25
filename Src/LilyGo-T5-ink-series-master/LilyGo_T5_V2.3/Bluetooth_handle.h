#ifndef  _BLUETOOTH_HANDLE_H
#define _BLUETOOTH_HANDLE_H
#endif

#include "BluetoothSerial.h"
#include "Arduino.h"
#include <WiFi.h>//to get MAC

extern BluetoothSerial SerialBT;

// #define BLUETOOTH_NAME "HNN_Device"

void Bluetooth_Init();
void Bluetooth_Read_String(String& outStr);
void Bluetooth_Write(String msg);
