#ifndef NETWORKING_H_INCLUDED
#define NETWORKING_H_INCLUDED

/*---------------------------------------------*/

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <process.h>
#include <stdatomic.h>

#pragma comment(lib, "Ws2_32.lib")

#define BUFLEN 512
#define PORT_MIN 1024
#define PORT_MAX 65536
//#define PORT 27015
//#define ADDRESS "127.0.0.1" // localhost

/*---------------------------------------------*/


// Dichiarazioni di funzioni

int init_winsock();
void cleanup_winsock();

char* get_local_IP_address();

SOCKET init_server(int port);
SOCKET handle_client(SOCKET listener, char** ip_address);
int connect_client(const char* ipAddress, int port, SOCKET* outClientSocket);
int send_message(SOCKET socket, const char *message, int len);
int receive_message(SOCKET socket, char *buffer, int buffer_len);

#endif // NETWORKING_H_INCLUDED
