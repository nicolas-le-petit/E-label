/* 
Date  : 31/07/2020
Author: DungTT
To handle application layer of storaging data in EEPROM. (base on <EEPROM.h>)
Including: 
Read/Write byte by byte
Reset data to default value
Show data storaging in EEPROM
 */

/*#ifndef _STORAGE_H_
#define _STORAGE_H_*/
#include "Storage.h"

#define _DEBUG_ 1
/*
@date: 28/07/2020
@brief: write a string data to EEPROM (C++ style :D), byte by byte
@para: start Address in EEPROM, max number of bytes need to write, pointer to string
 */
void Write_EEPROM(int add, int max_size, const char* inStr){
    for (int i=0; i<max_size; i++){
        EEPROM.write(add+i, inStr[i]);
        EEPROM.commit();
        delay(15);//need delay for a while to write data to EEPROM

        #if _DEBUG_
        Serial.print("Write into EEPROM at address: ");
        Serial.print(add+i);
        Serial.print("-");
        Serial.println(inStr[i]);
        #endif
    }
}

/*
@date: 28/07/2020
@brief: read a string data to EEPROM (Arduino style :D)
@para: start Address in EEPROM, max number of bytes need to read, return string without NULL
 */

//thinking about send pointer/address to this function to save memory
String Read_EEPROM(int add, int max_size){
    char outStr[max_size];
    String ans = "";
    for (int i = 0; i < max_size; i++)
    {
        if (EEPROM.read(add+i) == 255 || (char)EEPROM.read(add+i) =='\n' || (char)EEPROM.read(add+i) == '\0')
        {
            break;
        }
        outStr[i] = (char)EEPROM.read(add+i);
        delay(10);
        ans += outStr[i];
    }
    return ans;
  }

/*
@date: 31/07/2020
@brief: show EEPROM data
@para: start Address in EEPROM, number of bytes need to read
 */
void Show_Data_EEPROM(int startAdd, int size = EEPROM_SIZE){
    for (int i = startAdd; i < size; i++)
    {
        Serial.print((char)EEPROM.read(i));
        Serial.print("-");
    }
    Serial.println();
}

/*
@date: 31/07/2020
@brief: reset EEPROM data to default value (0XFF or 255)
@para: start Address in EEPROM, number of byte need to reset
@return: number of data writed
 */
int Reset_Data_EEPROM(int startAdd, int size){  
    int nbbyte;
    if (size > (EEPROM_SIZE - startAdd))
    {
        return -1;
    }
    for (nbbyte = startAdd; nbbyte < (size+startAdd); nbbyte++)
    {
        EEPROM.write(nbbyte, EEPROM_MASK);
        EEPROM.commit();
        delay(10);
    }
    return (nbbyte - startAdd); 
}

/*
@date: 31/08/2020
@brief: write a uint16 data to EEPROM(C++ style :D), 02 byte
@para: Address, data
 */
void Write_EEPROM_16(int add, uint16_t data){
    // uint16_t temp = data;
    uint8_t temp[2];
    temp[0] = data / 256;//big
    temp[1] = data % 256;//small

    EEPROM.write(add, temp[0]);
    EEPROM.commit();
    delay(15);//need delay for a while to write data to EEPROM

    EEPROM.write(add+1, temp[1]);
    EEPROM.commit();
    delay(15);//need delay for a while to write data to EEPROM
}

/*
@date: 31/08/2020
@brief: read a uint16 data from EEPROM(C++ style :D)
@para: Address, data
 */
uint16_t Read_EEPROM_16(int add){
    // uint16_t temp = data;
    uint8_t temp[2];
    temp[0] = EEPROM.read(add);//big
    temp[1] = EEPROM.read(add+1);//small

    uint16_t ans = temp[0] * 256 + temp[1];

    #if _DEBUG_
        Serial.print("Read uint16: ");
        // Serial.print(add);
        Serial.println(ans);
    #endif
    return ans;
}

/*
Just add here for remind :) 
 */
void EEPROM_Init(){
    EEPROM.begin(EEPROM_SIZE);
    delay(500);
}