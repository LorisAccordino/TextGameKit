#include "networking.h"


// Inizializzazione di WinSock
int init_winsock() {
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}

// Chiusura di WinSock
void cleanup_winsock() {
    WSACleanup();
}


// Funzione per ottenere l'indirizzo IP locale
char* get_local_IP_address() {
    static char ipAddress[INET_ADDRSTRLEN]; // Buffer per l'indirizzo IP
    char hostName[256];
    int result = gethostname(hostName, sizeof(hostName));
    if (result != 0) {
        return NULL; // Errore nell'ottenere il nome host
    }

    struct addrinfo *resultList = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; // Usa IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Ottieni l'elenco degli indirizzi associati al nome host
    result = getaddrinfo(hostName, NULL, &hints, &resultList);
    if (result != 0) {
        return NULL; // Errore nell'ottenere l'indirizzo IP
    }

    // Copia l'indirizzo IP dalla prima struttura addrinfo nell'array di caratteri ipAddress
    struct sockaddr_in *sockAddr = (struct sockaddr_in *)resultList->ai_addr;
    strcpy(ipAddress, inet_ntoa(sockAddr->sin_addr));

    // Rilascia la memoria allocata da getaddrinfo
    freeaddrinfo(resultList);

    return ipAddress;
}

// Funzione per "costruire" il socket
SOCKET build_socket() {
    SOCKET _socket;
    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_socket == INVALID_SOCKET)
    {
        cleanup_winsock();
        return NULL; // Errore durante la costruzione del socket
    }
    return _socket;
}

// Funzione per inizializzare il server
SOCKET init_server(int port) {
    int res, sendRes;

    // Costruzione del socket
    SOCKET listener = build_socket();
    if (listener == NULL) {
        return NULL; // Errore con la costruzione del socket
    }

    char* ip_address = malloc(INET_ADDRSTRLEN);
    ip_address = get_local_IP_address();
    if (ip_address == NULL) {
        cleanup_winsock();
        return NULL; // Errore ottenendo l'indirizzo IP
    }

    // Associa all'indirizzo IP
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_address);
    address.sin_port = htons(port);
    res = bind(listener, (struct sockaddr *)&address, sizeof(address));
    if (res == SOCKET_ERROR)
    {
        closesocket(listener);
        cleanup_winsock();
        return NULL; // Associazione fallita
    }

    // Imposta come listener
    res = listen(listener, SOMAXCONN);
    if (res == SOCKET_ERROR)
    {
        closesocket(listener);
        cleanup_winsock();
        return NULL; // Ascolto fallito
    }

    return listener;
}

// Funzione per gestire un client
SOCKET handle_client(SOCKET listener, char** ip_address) {
//char* handle_client(SOCKET listener) {
    // HANDLE A CLIENT ==========================

    // Accetta il socket client
    SOCKET client;

    struct sockaddr_in sa = {0}; /* for TCP/IP */
    socklen_t socklen = sizeof sa;
    client = accept(listener, (struct sockaddr *) &sa, &socklen);

    if (client == INVALID_SOCKET)
    {
        closesocket(listener);
        cleanup_winsock();
        return NULL; // Richiesta non accettata
    }

    // Indirizzo del client
    //return inet_ntoa(sa.sin_addr);
    //ip_address = malloc(INET_ADDRSTRLEN);
    //*ip_address = inet_ntoa(sa.sin_addr);
    //strcpy(ip_address, inet_ntoa(sa.sin_addr));

    *ip_address = (char*)malloc(sizeof(char) * INET_ADDRSTRLEN);
    strcpy(*ip_address, inet_ntoa(sa.sin_addr));  //  Can't assign strings like that. You need to copy it.

    return client;
}

// Funzione per connettere il client ad un server con IP e porta specificati
int connect_client(const char* ipAddress, int port, SOCKET* outClientSocket) {
    int res;

    // Costruzione del socket
    SOCKET client = build_socket();
    if (client == NULL) {
        return -1;
    }

    *outClientSocket = client;

    // Connettiti all'indirizzo IP e alla porta specificati
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ipAddress);
    address.sin_port = htons(port);
    res = connect(client, (struct sockaddr *)&address, sizeof(address));
    if (res == SOCKET_ERROR)
    {
        closesocket(client);
        cleanup_winsock();
        return res; // Connessione fallita
    }
    else if (client == INVALID_SOCKET)
    {
        cleanup_winsock();
        return -1; // Connessione fallita
    }

    return 0; // Connessione riuscita
}

// Funzione per inviare un messaggio
int send_message(SOCKET socket, const char *message, int len) {
    int sendRes = send(socket, message, len, 0);
    if (sendRes == SOCKET_ERROR) {
        //printf("Error sending: %d\n", WSAGetLastError());
        shutdown(socket, SD_BOTH);
        closesocket(socket);
        return SOCKET_ERROR;
    }
    return sendRes;
}

// Funzione per ricevere un messaggio
int receive_message(SOCKET socket, char *buffer, int buffer_len) {
    int res = recv(socket, buffer, buffer_len, 0);
    if (res > 0) {
        buffer[res] = '\0';
        return res;
    } else if (res == 0) {
        // Client disconnesso
        return -1;
    } else {
        return -1;
    }
    //return 0;
}
