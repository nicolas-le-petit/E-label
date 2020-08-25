/* 
Date  : 19/08/2020
Author: DungTT
To handle display task
Including: 
Init
Change Font size

*/

// include library, include base class, make path known
/* 
#include "SD.h"
#include "SPI.h"

#include <GxGDEH0213B72/GxGDEH0213B72.h>

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h> */
// FreeFonts from Adafruit_GFX
#include <GxEPD.h>
#include <Arduino.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

#include "Display_handle.h"

GxIO_Class io(SPI, /*CS=5*/ ELINK_SS, /*DC=*/ ELINK_DC, /*RST=*/ ELINK_RESET);
GxEPD_Class display(io, /*RST=*/ ELINK_RESET, /*BUSY=*/ ELINK_BUSY);

SPIClass sdSPI(VSPI);

const char *greeting = "Hello Everyone";
bool sdOK = false;
int startX = 0, startY = 0;

/*
@date : 16/08/2020
@brief: init SPI & Epaper
@para : none
@return: none
 */
void Epaper_init(){
    SPI.begin(SPI_CLK, SPI_MISO, SPI_MOSI, ELINK_SS);
    display.init(); // enable diagnostic output on Serial

    display.setRotation(1);
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&FreeMonoBold9pt7b);

    display.setCursor(display.width()/2 - 8, display.height());
    display.println(greeting);
    display.update();
    //return;
}

/*
@date : 16/08/2020
@brief: change font size
@para : font size
@return: font size if OK, 0 if can not
 */
byte Epaper_Change_Font_Size(byte fsize){
    switch (fsize){
        case 9: 
            display.setFont(&FreeMonoBold9pt7b);
            return 9;
        case 12:
            display.setFont(&FreeMonoBold12pt7b);
            return 12;
        case 18:
            display.setFont(&FreeMonoBold18pt7b);
            return 18;
        case 24:
            display.setFont(&FreeMonoBold24pt7b);
            return 24;    
        default:
            return 0;
    }

}

/*
@date : 16/08/2020
@brief: draw text
@para : string to display, x, y
@return: none
 */
void Epaper_Draw_Text(char* str2display, int x, int y){
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(display.width()/2 - 8, display.height() - 10);
    display.print(str2display);
    display.update();
}

/*
@date : 16/08/2020
@brief: draw text with endl
@para : string to display, x, y
@return: none
 */
void Epaper_Draw_Text_Endl(int x, int y, char* str2display){
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(display.width()/2 - 8, display.height() - 10);
    display.println(str2display);
    display.update();
}

/*
@date : 16/08/2020
@brief: draw bitmap
@para : image to display, x, y
@return: none
 */
void Epaper_Draw_Image(int x, int y, char* str2display){
    display.fillScreen(GxEPD_WHITE);

    // display.drawBitmap(image, startX, startY,  bmpWidth, bmpHeight, GxEPD_BLACK);
    
    display.update();
}

/*
@date : 25/08/2020
@brief: draw bitmap
@para : image to display, x, y
@return: none
 */
void Set_Cursor(int x, int y){
    display.setCursor(x, y);

    // display.drawBitmap(image, startX, startY,  bmpWidth, bmpHeight, GxEPD_BLACK);
    
    display.update();
}
/*
@date : 16/08/2020
@brief: init SD card & SPI
@para :
 */
bool SD_Card_init(){
    sdSPI.begin(SDCARD_CLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_SS);// use to save image

    if (!SD.begin(SDCARD_SS, sdSPI)) {
        sdOK = false;
    } else {
        sdOK = true;
    }
    return sdOK;
}