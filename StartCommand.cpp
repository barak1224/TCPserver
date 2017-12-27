/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "StartCommand.h"

StartCommand::StartCommand(map<string, int> *openGames) : openGames(openGames) {}

void StartCommand::execute(vector<string> args, ClientData data) {
    // args[0] is the name of the created game
    string roomName = args[0];
    int clientSocket = data.clientSocket;
    if (openGames->find(roomName) == openGames->end()) {
        string message = "exists";
        int n = write(clientSocket, &message, sizeof(message));
    } else {l

        this->openGames[roomName] = clientSocket;
        string message = "open";
        int n = write(clientSocket, &message, sizeof(message));
    }
}
