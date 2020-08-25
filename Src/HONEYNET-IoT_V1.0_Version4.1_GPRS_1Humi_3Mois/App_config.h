//Sketch uses 17286 bytes (56%) of program storage space. Maximum is 30720 bytes.
//Global variables use 680 bytes (33%) of dynamic memory, leaving 1368 bytes for local variables. Maximum is 2048 bytes.

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "ArduinoJson.h"
#include <EEPROM.h>
#include <String.h>

#define _TIMER_
//#define _DEBUG_

#ifdef _DEBUG_
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX chính là chân MOSI
#endif

// Khai bao MAC thiet bi, khac nhau giua cac thiet bi
String MAC = "";
String IMEI = "";
String SSN = "";

// Khai bao bien cho Analog_In
const int ADC1 = A0;
const int ADC2 = A1;
const int ADC3 = A6;
const int ADC4 = A7;

// Khai bao bien cho Digital IN
int LIST_VALUES_INPUT[] = {0, 0, 0, 0};
const byte LIST_PIN_INPUT[] = {9, 8, 7, 6};


// Khai bao thu vien
// Thu vien cho sensor nhiet do & do am (DHT)
#include "DHT.h"
// Khai bao loai sensor DHT
#define DHTTYPE DHT21
// Goi ham DHT de doc gia tri nhiet do & do am
DHT dht(ADC1, DHTTYPE);

// Dinh nghi chan dieu khien SIM
#define PWRKEY 12
#define NRESET 13

#define CMD 0
#define DATA 1
#define DEFAULT_TIMEOUT 10
#define DEFAULT_INTERCHAR_TIMEOUT 10000

// Den bao trang thai
const int RS1 = A2;
const int RS2 = A3;

uint32_t INTERVAL = 10;

// Định nghĩa vị trí các chân GPIO
const byte LIST_PIN_GPIO[] = {2, 3, 4, 5};

uint32_t interval_send_data = 1000;

uint32_t timer_send_data = 0;

uint32_t timer_control_gpio = 0;

uint32_t timer_update_info = 0;

uint32_t timer_reset_arduino = 0;
