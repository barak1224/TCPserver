#include <cstdlib>
#include "Server.h"

using namespace std;

/**
 * Global functions for the pthreads.
 */
void *acceptConnections(void *tArgs);
void *handleClient(void *clientSocket);

struct ClientData {
    int clientSocket;
    Server *server;
    pthread_t *threadID;
};

Server::Server(int port) : port(port), serverSocket(0) {
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
    int rc = pthread_create(acceptClientsThread, NULL, acceptConnections, (void *)server);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        exit(-1);
    }

    while(true) {
        string command;
        cin >> command;
        if (strcmp("exit", command.c_str()) == 0) {
            closeAllThreads();
            break;
        }
    }
}

void Server::initializeServer() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == ERROR) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress,
          sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
}

void *acceptConnections(void *tArgs) {
    Server *server = (Server *)tArgs;
    int serverSocket = server->getServerSocket();
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;

    vector<pthread_t*>threadsList = server->getThreadList();

    while (true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct
                sockaddr *)&clientAddress, &clientAddressLen);
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

        int rch = pthread_create(handleClientThread, NULL, handleClient, (void *) clientData);
        if (rch) {
            cout << "Error: unable to create thread, " << rch << endl;
            exit(-1);
        }
        // Close communication with the client
        close(clientSocket);
        delete handleClientThread;
    }
}

void *handleClient(void *clientData) {
    struct ClientData *data = (struct ClientData *)clientData;
    Server *server = data->server;
    int clientSocket = data->clientSocket;
    CommandsManager *manager = server->getCommandsManager();
    char buffer[MAX_LENGTH];
    int n = read(clientSocket, buffer, MAX_LENGTH);
    // get the commands
    string commandStr(buffer);
    string command = commandStr.substr(0, commandStr.find(" "));
    commandStr = commandStr.substr(commandStr.find(" "));
    char * commandChar;
    strcpy(commandChar,commandStr.c_str());
    vector<string> args;
    string separators = " ";
    char *tok = strtok (commandChar,separators.c_str());
    while (tok != NULL)
    {
        args.push_back(tok);
        tok = strtok (NULL, separators.c_str());
    }

    manager->executeCommand(command, args, data);
    pthread_exit(data->threadID);
}

