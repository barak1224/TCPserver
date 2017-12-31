/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "StartCommand.h"

StartCommand::StartCommand(map<string, int> *openGames) : openGames(openGames) {}

void StartCommand::execute(vector<string> args, int clientSocket1, int clientSocket2) {
    // args[0] is the name of the created game
    string roomName = args[0];
    if (openGames->find(roomName) != openGames->end()) {
        string message = FAILURE;
        sendToClient(clientSocket1, message);
    } else {
        (*openGames)[roomName] = clientSocket1;
    }
}

void StartCommand::sendToClient(int clientSocket, string message) const {
    int n = write(clientSocket, &message, sizeof(message));
    if (n == ERROR)
        throw "Error writing to client " + message;
}