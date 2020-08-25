#include "SD.h"
#include "SPI.h"
#include <GxEPD.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include <GxGDEW027W3/GxGDEW027W3.h>    // 2.7" b/w
// #include <GxGDEW027C44/GxGDEW027C44.h>    // 2.7" b/w/r  

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

int bmpWidth = 230, bmpHeight = 60;
//width:230,height:60
const unsigned char lilygo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x8e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xf3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0xff, 0xf9, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0xff, 0xf9, 0xc0, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x71, 0xf9, 0xf8, 0xc0, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0xff, 0xf8, 0x00, 0x03, 0xff, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x71, 0xf8, 0xfc, 0xc0, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 0xf0, 0x00, 0xf1, 0xf8, 0xfc, 0x60, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0xff, 0xf0, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x07, 0xff, 0xff, 0xfc, 0x00, 0xf1, 0xf8, 0xfc, 0x60, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0x01, 0xff, 0xf0, 0x00, 0xff, 0xff, 0xff, 0x80, 0x0f, 0xff, 0xff, 0xfe, 0x00, 0xf1, 0xff, 0xf8, 0x60, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0x01, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x1f, 0xff, 0xff, 0xff, 0x00, 0xf1, 0xff, 0xf8, 0x60, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0x03, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0xf1, 0xff, 0xf0, 0x60, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0x83, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xff, 0x80, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0xf1, 0xff, 0xe0, 0x60, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x0f, 0xff, 0x87, 0xff, 0x80, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x71, 0xff, 0xe0, 0x60, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x0f, 0xff, 0x87, 0xff, 0x80, 0x0f, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x71, 0xff, 0xf0, 0x60, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xc7, 0xff, 0x00, 0x1f, 0xff, 0x81, 0xfc, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x79, 0xff, 0xf0, 0x40, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xcf, 0xff, 0x00, 0x1f, 0xff, 0x00, 0x78, 0x00, 0xff, 0xff, 0x3f, 0xff, 0xf0, 0x79, 0xfb, 0xf0, 0x40, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x03, 0xff, 0xcf, 0xfe, 0x00, 0x3f, 0xff, 0x00, 0x30, 0x01, 0xff, 0xfe, 0x0f, 0xff, 0xf8, 0x3d, 0xf9, 0xf8, 0x80, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfe, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x0f, 0xff, 0xf8, 0x3f, 0xf9, 0xf8, 0x80, 0x1f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x3f, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xfc, 0x07, 0xff, 0xf8, 0x1f, 0xf1, 0xf8, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x01, 0xff, 0xfc, 0x03, 0xff, 0xfc, 0x1f, 0x80, 0xff, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x03, 0xff, 0xfc, 0x0f, 0xe0, 0x1e, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x03, 0xff, 0xfc, 0x03, 0xf8, 0x3c, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf0, 0x00, 0x7f, 0xfc, 0x1f, 0xff, 0xc3, 0xff, 0xfc, 0x01, 0xff, 0xfc, 0x01, 0xff, 0xf8, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x7f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x7f, 0xfc, 0x3f, 0xff, 0xc3, 0xff, 0xfc, 0x01, 0xff, 0xfc, 0x00, 0xff, 0xf0, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x3f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0x7f, 0xfc, 0x3f, 0xff, 0xc3, 0xff, 0xfc, 0x01, 0xff, 0xfc, 0x00, 0x1f, 0x80, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x3f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x7f, 0xfc, 0x3f, 0xff, 0xc3, 0xff, 0xfc, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x3f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xc0, 0x00, 0x7f, 0xfc, 0x3f, 0xff, 0xc3, 0xff, 0xfc, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x3f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x7f, 0xfc, 0x3f, 0xff, 0xc3, 0xff, 0xfc, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x3f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x3f, 0xfc, 0x3f, 0xff, 0xc1, 0xff, 0xfc, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x3f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x3f, 0xfe, 0x3f, 0xff, 0xc1, 0xff, 0xfe, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x3f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x3f, 0xfe, 0x3f, 0xff, 0xc1, 0xff, 0xfe, 0x01, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x3f, 0xfc, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x3f, 0xff, 0x03, 0xff, 0xc1, 0xff, 0xff, 0x01, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x3f, 0xf8, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x3f, 0xff, 0x80, 0xff, 0xc0, 0xff, 0xff, 0x03, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x3f, 0xfc, 0x1f, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xc0, 0xff, 0xc0, 0xff, 0xff, 0xc3, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xfc, 0x00, 0x3f, 0xfc, 0x1f, 0xff, 0xfc, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xf0, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xfc, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xc0, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xc0, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xfc, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x80, 0x07, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x80, 0x07, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x3f, 0xf8, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf0, 0x3f, 0xf0, 0x03, 0xff, 0xff, 0xf0, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x3f, 0xf0, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0xe0, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#if defined(_GxGDEW0154Z04_H_) || defined(_GxGDEW0213Z16_H_) || defined(_GxGDEW029Z10_H_) || defined(_GxGDEW027C44_H_)
#define HAS_RED_COLOR
#endif

#if defined(_GxGDEW027C44_H_)
const char *skuNum = "SKU:H220";
int startX = 30, startY = 50;
#elif defined(_GxGDEW027W3_H_)
const char *skuNum = "SKU:H225";
int startX = 30, startY = 50;
#endif

#define SPI_MOSI        23
#define SPI_MISO        -1
#define SPI_CLK         18

#define ELINK_SS        5
#define ELINK_BUSY      4
#define ELINK_RESET     16
#define ELINK_DC        17

#define SDCARD_SS       13
#define SDCARD_CLK      14
#define SDCARD_MOSI     15
#define SDCARD_MISO     2

#define BUTTON_1        37
#define BUTTON_2        38
#define BUTTON_3        39

#define IIS_BCK         26
#define IIS_WS          25
#define IIS_DOUT        19

#define ICS43434
#define ICS_IIS_WS      33
#define ICS_IIS_BCK     32
#define ICS_IIS_DIN     27

GxIO_Class io(SPI, ELINK_SS, ELINK_DC, ELINK_RESET);
GxEPD_Class display(io, ELINK_RESET, ELINK_BUSY);
SPIClass sdSPI(VSPI);


bool sdOK = false;

void setup()
{
    pinMode(BUTTON_1, INPUT);
    pinMode(BUTTON_2, INPUT);
    pinMode(BUTTON_3, INPUT);

    Serial.begin(115200);

    SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, ELINK_SS);
    display.init(); // enable diagnostic output on Serial
    display.setRotation(1);
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(0, 0);

    sdSPI.begin(SDCARD_CLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_SS);
    if (!SD.begin(SDCARD_SS, sdSPI)) {
        sdOK = false;
    } else {
        sdOK = true;
    }
#if defined(HAS_RED_COLOR)
    display.drawBitmap(lilygo, startX, startY,  bmpWidth, bmpHeight, GxEPD_RED);
#elif defined(_GxGDEW027W3_H_)
    display.drawBitmap(lilygo, startX, startY,  bmpWidth, bmpHeight, GxEPD_WHITE);
#endif

    display.setCursor(display.width()  - display.width() / 2 - 20, display.height() - 35);

#if defined(HAS_RED_COLOR)
    display.setTextColor(GxEPD_RED);
#endif
    display.println(skuNum);

    display.setTextColor(GxEPD_BLACK);

    display.setCursor(display.width()   / 2 - 60, display.height() - 10);

    if (sdOK) {
        uint32_t cardSize = SD.cardSize() / (1024 * 1024);
        display.println("SDCard:" + String(cardSize) + "MB");
    } else {
        display.println("SDCard  None");
    }
    display.update();
}

void loop()
{
    if (digitalRead(BUTTON_1) == LOW) {
        display.update(); delay(500);
    } else if (digitalRead(BUTTON_2) == LOW) {
        display.update(); delay(500);
    } else if (digitalRead(BUTTON_3) == LOW) {
        esp_sleep_enable_ext0_wakeup((gpio_num_t )BUTTON_3, LOW);
        esp_deep_sleep_start();
    }
}