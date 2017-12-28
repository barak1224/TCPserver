/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "CloseCommand.h"

CloseCommand::CloseCommand(map<string, int> *openGames, map<string, GameroomData> *lobbyMap) : openGames(openGames),
                                                                                               lobbyMap(lobbyMap) {}

void CloseCommand::execute(vector<string> args, int clientSocket) {
    string roomName = args[0];
    if (openGames->find(roomName) == openGames->end()) {
        sendToClient(clientSocket, "failure");
    } else {
        openGames->erase(roomName);
    }
}


void CloseCommand::sendToClient(int clientSocket, string message) const {
    int n = write(clientSocket, &message, sizeof(message));
    if (n == ERROR)
        throw "Error writing to client " + message;
}