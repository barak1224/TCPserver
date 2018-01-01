#include <cstdlib>
#include "Server.h"

using namespace std;

/**
 * Global functions for the pthreads.
 */
void *acceptConnections(void *tArgs);

void *handleClient(void *clientSocket);


pthread_mutex_t mutex;

Server::Server(int port) : port(port), serverSocket(0) {
    this->connectedClients = 0;
    this->commandsManager = new CommandsManager();
    cout << "Server" << endl;
}


void Server::stop() {
    close(serverSocket);
}

void Server::start() {
    initializeServer();
    pthread_t *acceptClientsThread = new pthread_t();
    Server *server = this;
    int rc = pthread_create(acceptClientsThread, NULL, acceptConnections, (void *) server);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }

    while (true) {
        string command;
        cin >> command;
        if (strcmp("exit", command.c_str()) == 0) {
            break;
        }
    }
    pthread_join(*acceptClientsThread, NULL);
    delete acceptClientsThread;
}

void Server::initializeServer() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == ERROR) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
}

void *acceptConnections(void *tArgs) {
    Server *server = (Server *) tArgs;
    int serverSocket = server->getServerSocket();
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;

    vector<pthread_t *> threadsList = server->getThreadList();


    listen(serverSocket, MAX_CONNECTED_CLIENTS);

    while (true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct
                sockaddr *) &clientAddress, &clientAddressLen);

        pthread_mutex_lock(&mutex);
        server->connectedClients++;
        pthread_mutex_unlock(&mutex);

        cout << "Client connected" << endl;
        if (clientSocket == -1)
            throw "Error on accept";

        // create the thread that will handle the client
        pthread_t *handleClientThread = new pthread_t();
        threadsList.push_back(handleClientThread);              // save the thread on the list

        ClientData *clientData = new struct ClientData();    // create the struct for the data
        clientData->clientSocket = clientSocket;
        clientData->server = server;
        clientData->threadID = handleClientThread;

        ClientHandler h;
        int rch = pthread_create(handleClientThread, NULL, ClientHandler::handleClient, (void *) clientData);
        if (rch) {
            cout << "Error: unable to create thread, " << rch << endl;
            exit(-1);
        }
        // Close communication with the client
        pthread_join(*handleClientThread, NULL);
        close(clientSocket);
        delete handleClientThread;
    }
}

bool Server::readFrom(int clientSocket, char *arr) {
    // Read new move from the client
    int n = read(clientSocket, arr, MAX_LENGTH);
    cout << arr << endl;
    return checkForErrors(n);
}

bool Server::writeTo(int clientSocket, char arr[MAX_LENGTH]) {
    // Write new move to the client
    int n = write(clientSocket, arr, MAX_LENGTH);
    return checkForErrors(n);
}

bool Server::checkForErrors(int n) {
    if (n == ERROR) {
        cout << "Error reading chosen move" << endl;
        return false;
    }
    if (n == DISCONNECT) {
        cout << "Client disconnected" << endl;
        return false;
    }
    return true;
}