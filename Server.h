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
#define MAX_MOVE 7
#define PLAYER_1 0
#define PLAYER_2 1

class Server {
public:
    Server(int port);
    void start();
    void stop();
private:
    // Struct which store data client
    struct DataClient {
        struct sockaddr_in clientAddress;
        socklen_t clientLen;
    };
    int clientSockets[2];
    DataClient dataClients[2];
    int port;
    int serverSocket; // the socket's file descriptor
    /**
     * The method read from the client socket and store inside arr
     * @return true for success, otherwise false
     */
    bool readFrom(int clientSocket, char arr[MAX_MOVE]);
    /**
     * The method write from the client socket and store inside arr
     * @return true for success, otherwise false
     */
    bool writeFrom(int clientSocket, char arr[MAX_MOVE]);
    /**
     * The method initializing the server
     */
    void initializeServer();
    /**
     * The method accepting the two clients
     * @return ERROR or VALID
     */
    int acceptTwoClients();
    /**
     * The method makes a turn
     * @return false if there was a problem, otherwise true
     */
    bool playTurn(int clientSocket1, int clientSocket2);
    /**
     * The method getting a number and decipher the error
     * @return error decipher or valid
     */
    bool checkForErrors(int n);
    /**
     * The method sends to the players their's numbers;
     * @return status of sending
     */
    int sendPlayersNumbers();

    bool parseDataForEnd(char[MAX_MOVE]);
};


#endif //SERVER_SERVER_H
