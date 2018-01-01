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
        cout << "Client " << clientSocket1 << " opened game " << roomName << endl;
        (*openGames)[roomName] = clientSocket1;
        cout << openGames->size() << " open games" << endl;
    }
}

void StartCommand::sendToClient(int clientSocket, string message) const {
    char *convert = new char[MAX_LENGTH];
    memset(convert, 0, MAX_LENGTH);
    strcpy(convert, message.c_str());
    int n = write(clientSocket, &message, sizeof(message));
    delete convert;
    if (n == ERROR)
        throw "Error writing to client " + message;
}