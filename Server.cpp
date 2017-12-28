#include "Server.h"

using namespace std;

Server::Server(int port) : port(port), serverSocket(0) {
    cout << "Server" << endl;
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

int Server::acceptTwoClients() {
    // Accept a new client connection
    for (int playerNumber = 0; playerNumber < 2; playerNumber++) {
        dataClients[playerNumber].clientLen=0;
        clientSockets[playerNumber] = accept(serverSocket,
                                             (struct sockaddr *) &(dataClients[playerNumber].clientAddress),
                                             &(dataClients[playerNumber].clientLen));
        if (clientSockets[playerNumber] < 0) {
            return ERROR;
        }
        cout << "Client " << playerNumber + 1 << " connected" << endl;
        if (playerNumber == 0) {
            int sendPlayerNumber = playerNumber + 1;
            int n = write(clientSockets[playerNumber], &sendPlayerNumber, sizeof(sendPlayerNumber));
            if (n == ERROR) {
                cout << "Error writing to socket" << endl;
                return ERROR;
            }
        }
    }
    return VALID;
}

void Server::start() {
    initializeServer();
    while (true) {
        cout << "Waiting for client connections..." << endl;
        if (acceptTwoClients() == ERROR) { throw "Error on accept"; }
        if (sendPlayersNumbers() == ERROR) { throw "Error on accept"; }
        bool play = true;
        while (play) {
            play = playTurn(clientSockets[PLAYER_1], clientSockets[PLAYER_2]);
            if (play) {
                play = playTurn(clientSockets[PLAYER_2], clientSockets[PLAYER_1]);
            }
        }
        // Close communication with the client
        close(clientSockets[PLAYER_1]);
        close(clientSockets[PLAYER_2]);
    }
}

bool Server::playTurn(int clientSocket1, int clientSocket2) {
    char arr[MAX_MOVE];
    memset(arr, 0, MAX_MOVE);
    bool continuePlay;
    continuePlay = readFrom(clientSocket1, arr);
    bool parse = parseDataForEnd(arr);
    if (continuePlay) {
        continuePlay = writeFrom(clientSocket2, arr);
    }
    if (parse || (strcmp(arr,"End") == 0)) {
        continuePlay = false;
    }
    return continuePlay;
}

// Handle requests from a specific client
bool Server::readFrom(int clientSocket, char *arr) {
    // Read new move from the client
    int n = read(clientSocket, arr, MAX_MOVE);
    return checkForErrors(n);
}

bool Server::writeFrom(int clientSocket, char arr[MAX_MOVE]) {
    // Write new move to the client
    int n = write(clientSocket, arr, MAX_MOVE);
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

int Server::sendPlayersNumbers() {
    for (int playerNumber = 0; playerNumber < 2; playerNumber++) {
        int sendPlayerNumber = playerNumber + 1;
        int n = write(clientSockets[playerNumber], &sendPlayerNumber, sizeof(sendPlayerNumber));
        if (n == ERROR) {
            cout << "Error writing to socket" << endl;
            return ERROR;
        }
    }
    return VALID;
}

void Server::stop() {
    close(serverSocket);
}

bool Server::parseDataForEnd(char *arr) {
    string s = arr;
    if (string::npos == s.find('x')) {
        return false;
    }
    s = s.substr(0, s.find('x'));
    strcpy(arr, s.c_str());
    return true;
}
