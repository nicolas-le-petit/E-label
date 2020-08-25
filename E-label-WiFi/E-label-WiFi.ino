/* 
Date  : 17/08/2020
Author: DungTT
To handle application layer of storaging data in EEPROM. (base on <EEPROM.h>)
Including: 
Read/Write byte by byte
Reset data to default value
Show data storaging in EEPROM
 */
#include "main.h"

//const int bmpWidth = 250, bmpHeight = 122;
//width:150,height:39
const unsigned char image[] = {};

void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println("setup");

    Epaper_init();

/*     Serial.println("Display information:");
    Serial.print("Width: ");
    Serial.println(display.width());
    Serial.print("Height: ");
    Serial.println(display.height()); */

    goToDeepSleep();
}


void loop()
{
}
