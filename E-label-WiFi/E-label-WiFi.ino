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
#include "Unit_Test.h"

//const int bmpWidth = 250, bmpHeight = 122;

// const unsigned char image[] = {};

void setup()
{
    Serial.begin(115200);
    Serial.println("Set up ok!");

    EEPROM.begin(EEPROM_SIZE);
    delay(500);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Epaper_Init();
    Core_Task_Init();
}


void loop()
{
    // Unit_Test_Handle();
}
