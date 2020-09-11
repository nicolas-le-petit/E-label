/* #define IP_SERVER "192.168.99.102"
#define PORT_SERVER 80 */
// #include "Storage.h"
#ifndef  _CORETASK_HANDLE_H
#define _CORETASK_HANDLE_H
typedef struct msg_server_pack{
    bool is_parse_ok;
    String status_connect;
    String item;
    String price;
    String currency;
    String note;
    int thisTime;
    int nextTime;
    String QRcode;
    // byte QRcode[];
};
#endif

/* #ifdef __cplusplus
extern "C" {
#endif */

enum CoreTask_Mode
{
	CONFIG_MODE,
    RUN_MODE,
    ERROR,
    INIT_MODE,
};

#define TIME_WAKE_UP_INTERVAL_NORMAL 60//in minute -> maximum sleep 400 days (uint64_t)
#define TIME_WAKE_UP_INTERVAL_ERROR 1//in minute
#define TIME_CHECK_BUTTON_PRESS 2000

#define BUTTON_PIN 39
#define QR_CODE_BUFFER 730

String Send_Request_to_Server();
bool parse_data_wifi(String json);

int Core_Task_Init();
int Config_Mode_Handle();
int Run_Mode_Handle();
bool Check_Config_Mode(unsigned long timeout);