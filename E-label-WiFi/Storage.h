/*#include "Storage.h"*/

#ifndef _STORAGE_H_
#define _STORAGE_H_
#endif

/* #ifdef __cplusplus
extern "C" {
#endif */

#include <EEPROM.h>
#include <stdint.h>
#define EEPROM_MASK 255//value by default of EEPROM
#define EEPROM_SIZE 200
/* #define DEVICE_NAME_ADDRESS 00
#define DEVICE_VERSION_ADDRESS 06 */

#define USER_LOGIN_ADDRESS 00
#define PASS_LOGIN_ADDRESS 25
#define WIFI_SSID_ADDRESS 50//address to storage data for ssid is 50 -> 74
#define WIFI_PASSWORD_ADDRESS 75//address to storage data for password is 75 -> 99
#define HOST_ADDRESS 100//100 -> 124
#define SERVER_PORT_ADDRESS 125//125 -> 126

#define WIFI_SSID_BUFFER_MAX 25
#define WIFI_PW_BUFFER_MAX 25
#define USER_LOGIN_BUFFER_MAX 25
#define PASS_LOGIN_BUFFER_MAX 25
#define IP_SERVER_BUFFER_MAX 25
#define SERVER_PORT_BUFFER_MAX 2

/* #define DEVICE_NAME_BUFFER_MAX 6
#define DEVICE_VERSION_BUFFER_MAX 14
#define MAC_ID_BUFFER_MAX 12 */

void Write_EEPROM(int add, int max_size, const char* inStr);
String Read_EEPROM(int add, int max_size);
void Show_Data_EEPROM(int startAdd, int size);
int Reset_Data_EEPROM(int startAdd, int size);
void EEPROM_Init();
uint16_t Read_EEPROM_16(int add);
void Write_EEPROM_16(int add, uint16_t data);