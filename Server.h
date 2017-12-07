#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <cstring>

#define ERROR -1
#define VALID 1
#define DISCONNECT 0
#define MAX_CONNECTED_CLIENTS 2
#define MAX_MOVE 9

class Server {
public:
    Server(int port);
    void start();
    void stop();
private:
    struct DataClient {
        struct sockaddr_in clientAddress;
        socklen_t clientLen;
    };
    int clientSockets[2];
    DataClient dataClients[2];
    int port;
    int serverSocket; // the socket's file descriptor
    bool readFrom(int clientSocket, char arr[MAX_MOVE]);
    bool writeFrom(int clientSocket, char arr[MAX_MOVE]);
    void initializeServer();
    int acceptTwoClients();
    bool playTurn(int clientSocket1, int clientSocket2);
    bool checkForErrors(int n);
    int sendPlayersNumbers();
};


#endif //SERVER_SERVER_H
