// include library, include base class, make path known
#ifndef  _DISPLAY_HANDLE_H
#define _DISPLAY_HANDLE_H
#endif

/* #ifdef __cplusplus
extern "C" {
#endif */

#include <GxEPD.h>
// #include "SD.h"
#include "SPI.h"

#include <GxGDEH0213B72/GxGDEH0213B72.h>
// FreeFonts from Adafruit_GFX
/* #include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h> */

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

extern GxIO_Class io;
extern GxEPD_Class display;

extern SPIClass sdSPI;

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

/* #define go_to_home() display.setCursor(0, 0)
#define cls() display.fillScreen(GxEPD_WHITE) */

bool SD_Card_init();
void Epaper_Init();
byte Epaper_Change_Font_Size(byte fsize);
void Epaper_Draw_Text(char* str2display, int x, int y);
void Epaper_Draw_Image(char* str2display, int x, int y);
// void display_price(const char* item, const char* price, const char* currency, const unsigned char QRcode[]);
void display_price(String item, String price, String currency, const unsigned char QRcode[]);