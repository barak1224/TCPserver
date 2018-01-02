#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#define ERROR -1
#define VALID 1
#define DISCONNECT 0
#define MAX_CONNECTED_CLIENTS 2
#define MAX_LENGTH 30

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <cstring>
#include <pthread.h>

using namespace std;

#include "CommandsManager.h"
#include "ClientHandler.h"



class Server {
public:
    Server(int port);
    ~Server();
    void start();
    void stop();
    int connectedClients;

    int getServerSocket() { return this->serverSocket; }

    vector<pthread_t>* getThreadList() {return this->threadsList;}

    CommandsManager* getCommandsManager() { return this->commandsManager;}

    static bool writeTo(int clientSocket, string message);

    static bool readFrom(int clientSocket, string &message);

private:
    int port;
    int serverSocket; // the socket's file descriptor
    CommandsManager *commandsManager;
    vector<pthread_t> *threadsList;
    vector<int> socketsList; // to send them that the server disconnected

    /**
     * The method initializing the server
     */
    void initializeServer();

    static bool checkForErrors(int n);
};

struct ClientData {
    int clientSocket;
    Server *server;
    pthread_t threadID;
};

#endif //SERVER_SERVER_H
