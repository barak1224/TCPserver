#include <cstdlib>
#include "Server.h"

using namespace std;

/**
 * Global functions for the pthreads.
 */
void *acceptConnections(void *tArgs);

pthread_mutex_t mutex;

Server::Server(int port) : port(port), serverSocket(0) {
    this->threadsList = new vector<pthread_t>();
    this->connectedClients = 0;
    this->commandsManager = new CommandsManager();
    cout << "Server" << endl;
}

Server::~Server() {
    delete commandsManager;
    threadsList->clear();
    delete threadsList;
}

void Server::stop() {
    close(serverSocket);
}

void Server::start() {
    initializeServer();
    pthread_t acceptClientsThread;
    Server *server = this;
    int rc = pthread_create(&acceptClientsThread, NULL, acceptConnections, (void *) server);
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
    int numOfSockets = socketsList.size();
    for (int j = 0; j < numOfSockets; j++) {
        close(socketsList.at(j));
    }
    pthread_cancel(acceptClientsThread);
    int numOfThreads = this->threadsList->size();
    for (int i = 0; i < numOfThreads; i++) {
        pthread_cancel(threadsList->at(i));
    }
    exit(0);
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

    vector<pthread_t> *threadsList = server->getThreadList();


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
        pthread_t handleClientThread;
        threadsList->push_back(handleClientThread);              // save the thread on the list

        ClientData clientData;    // create the struct for the data
        clientData.clientSocket = clientSocket;
        clientData.server = server;
        clientData.threadID = handleClientThread;
        int rch = pthread_create(&handleClientThread, NULL, ClientHandler::handleClient, (void *) &clientData);
        if (rch) {
            cout << "Error: unable to create thread, " << rch << endl;
            exit(-1);
        }
    }
}

bool Server::readFrom(int clientSocket, string &message) {
    int i = 0, n;
    char buffer;
    while (true) {
        n = read(clientSocket, &buffer, sizeof(char));
        if (ERROR == n) {
            cout << "Failed writing to client " << clientSocket << endl;
            return false;
        }
        if (buffer == '\0') break;
        message += buffer;
        i++;
    }
    if (n == DISCONNECT) {
        cout << "Client " << clientSocket << " disconnected" << endl;
        return false;
    }
    return true;
}

bool Server::writeTo(int clientSocket, string message) {
    char buffer;
    int i = 0, n;
    while (i < message.length()) {
        buffer =  message.at(i);
        n = write(clientSocket, &buffer, sizeof(char));
        if (ERROR == n) throw "Error sending message";
        i++;
    }
    buffer = '\0';
    n = write(clientSocket, &buffer, sizeof(char));
    if (ERROR == n)
        cout << "Failed writing to client " << clientSocket << endl;
    if (n == DISCONNECT)
        cout << "Client " << clientSocket <<" disconnected" << endl;
    return (n != DISCONNECT && n != ERROR); // true if success, else false
}

bool Server::checkForErrors(int n) {
    if (n == ERROR) {
        cout << "Error reading" << endl;
        return false;
    }
    if (n == DISCONNECT) {
        cout << "Client disconnected" << endl;
        return false;
    }
    return true;
}

