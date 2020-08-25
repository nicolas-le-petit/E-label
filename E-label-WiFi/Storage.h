/*#include "Storage.h"*/
#include <EEPROM.h>
/*#ifndef _STORAGE_H_
#define _STORAGE_H_*/

#define EEPROM_MASK 255//value by default of EEPROM
#define EEPROM_SIZE 200
/* #define DEVICE_NAME_ADDRESS 00
#define DEVICE_VERSION_ADDRESS 06 */

#define USER_LOGIN_ADDRESS 00
#define PASS_LOGIN_ADDRESS 25
#define WIFI_SSID_ADDRESS 50//address to storage data for ssid is 50 -> 74
#define WIFI_PASSWORD_ADDRESS 75//address to storage data for password is 75 -> 99
#define IP_SERVER_ADDRESS 100//100 -> 114
#define SERVER_PORT_ADDRESS 115//115 -> 119

#define WIFI_SSID_BUFFER_MAX 25
#define WIFI_PW_BUFFER_MAX 25
#define USER_LOGIN_BUFFER_MAX 25
#define PASS_LOGIN_BUFFER_MAX 25
#define IP_SERVER_BUFFER_MAX 15
#define SERVER_PORT_BUFFER_MAX 5

/* #define DEVICE_NAME_BUFFER_MAX 6
#define DEVICE_VERSION_BUFFER_MAX 14
#define MAC_ID_BUFFER_MAX 12 */

void Write_EEPROM(int add, int max_size, const char* inStr);
String Read_EEPROM(int add, int max_size);
void Show_Data_EEPROM(int startAdd, int size);
int Reset_Data_EEPROM(int startAdd, int size);