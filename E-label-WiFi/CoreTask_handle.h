/* #define IP_SERVER "192.168.99.102"
#define PORT_SERVER 80 */
// #include "Storage.h"

bool Send_Request_to_Server(String host, int httpPort);
bool parse_data(WiFiClient client_response, String json);
const char* Load_Server_Address();
int Load_Server_Port();