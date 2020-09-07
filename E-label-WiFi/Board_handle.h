#ifndef  _BOARD_HANDLE_H
#define _BOARD_HANDLE_H
#endif

/* #ifdef __cplusplus
extern "C" {
#endif */

#include <WiFi.h>
// #include "driver/adc.h"
#include <esp_wifi.h>
#include <esp_bt.h>
#include <stdint.h>

// How many minutes the ESP should sleep
// #define DEEP_SLEEP_TIME 1
#define BASE_TIME_US 1000000 // base time in us
#define BASE_TIME_MINUTE 60 //60s in a minute

//just select ONE
#define SET_CPU_80MHZ setCpuFrequencyMhz(80);
#define SET_CPU_160MHZ setCpuFrequencyMhz(160);
#define SET_CPU_240MHZ setCpuFrequencyMhz(240);

#define NUM_SAMPLES 9
#define BATTERY_METTER_PIN 35
// #define WIFI_TIMEOUT 15 // 15seconds in milliseconds

void goToDeepSleep(uint32_t interval);
int get_Batery_Value();