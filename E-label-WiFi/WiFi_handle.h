#ifndef _WIFI_HANDLE_H_
#define _WIFI_HANDLE_H_
#endif

/* #ifdef __cplusplus
extern "C" {
#endif */

#include "Arduino.h"
#include "Storage.h"
#include <WiFi.h>
#include "Board_handle.h"
#include "Display_handle.h"
#include "Config_handle.h"

/* void Config_SSID_Password(const char* ssid, const char* password);
void Load_SSID_Password(const char* ssid, const char* password); */
bool Wifi_Connect();
// void Wifi_Connect(const char* & ssid, const char* & password);
/*void WiFi_Init(const char* _ssid, const char* _password);*/