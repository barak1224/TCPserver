/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "StartCommand.h"

StartCommand::StartCommand(map<string, int> *openGames) : openGames(openGames) {}

void StartCommand::execute(vector<string> args, ClientData *data) {
    // args[0] is the name of the created game
    string roomName = args[0];
    int clientSocket = data->clientSocket;
    if (openGames->find(roomName) != openGames->end()) {
        string message = "failure";
        sendToClient(clientSocket, message);
    } else {
        (*openGames)[roomName] = clientSocket;
        string message = "success";
        int n = write(clientSocket, &message, sizeof(message));
        // the socket stays open in case someone joins
    }
}

void StartCommand::sendToClient(int clientSocket, string message) const {
    int n = write(clientSocket, &message, sizeof(message));
    if (n == ERROR)
        throw "Error writing to client " + message;
}