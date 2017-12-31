/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "JoinCommand.h"

JoinCommand::JoinCommand(map<string, int> *openGames, map<string, GameroomData> *lobbyMap) : openGames(openGames),
                                                                                             lobbyMap(lobbyMap) {}

void JoinCommand::execute(vector<string> args, int clientSocket2) {
    string roomName = args[0];
    if (openGames->find(roomName) != openGames->end()) {
        int clientSocket1 = (*openGames)[roomName];
        GameroomData roomData;
        roomData.socket1 = clientSocket1;
        roomData.socket2 = clientSocket2;
        roomData.name = roomName;
        openGames->erase(roomName);
        (*lobbyMap)[roomName] = roomData;

        //send numbers to the players
        sendToClient(clientSocket1, "1");
        sendToClient(clientSocket2, "2");

    } else {
        sendToClient(clientSocket2, FAILURE);
    }
}

void JoinCommand::sendToClient(int clientSocket, string message) const {
    int n = write(clientSocket, &message, sizeof(message));
    if (n == ERROR)
        throw "Error writing to client " + message;
}