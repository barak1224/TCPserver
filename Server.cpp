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
        clientSockets[playerNumber] = accept(serverSocket, (struct sockaddr *) &dataClients[playerNumber].clientAddress,
                                             &dataClients[playerNumber].clientLen);
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
            play = playTurn(clientSockets[0], clientSockets[1]);
            if (play) {
                play = playTurn(clientSockets[1], clientSockets[0]);
            }
        }
        // Close communication with the client
        close(clientSockets[0]);
        close(clientSockets[1]);
    }
}

bool Server::playTurn(int clientSocket1, int clientSocket2) {
    char arr[MAX_MOVE];
    bool continuePlay;
    continuePlay = readFrom(clientSocket1, arr);
    if (strcmp(arr, "END") == 0) {
        continuePlay = false;
    } else if (continuePlay) {
        continuePlay = writeFrom(clientSocket2, arr);
    }
    return continuePlay;
}

// Handle requests from a specific client
bool Server::readFrom(int clientSocket, char *arr) {
    // Read new move from the client
    int n = read(clientSocket, arr, sizeof(char) * MAX_MOVE);
    return checkForErrors(n);
}

bool Server::writeFrom(int clientSocket, char arr[MAX_MOVE]) {
    // Write new move to the client
    int n = write(clientSocket, arr, sizeof(char) * MAX_MOVE);
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