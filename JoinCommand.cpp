/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "JoinCommand.h"

JoinCommand::JoinCommand(map<string, int> *openGames, map<string, GameroomData *> *lobbyMap) : openGames(openGames),
                                                                                               lobbyMap(lobbyMap) {}

void JoinCommand::execute(vector<string> args, int clientSocket2, int clientSocketSpare) {
    string roomName = args[0];
    if (openGames->find(roomName) != openGames->end()) {    //success in finding the room
        cout << "Client " << clientSocket2 <<" is connecting to room " + roomName << endl;
        int clientSocket1 = (*openGames)[roomName];
        GameroomData *roomData = new GameroomData();
        roomData->socket1 = clientSocket1;
        roomData->socket2 = clientSocket2;
        roomData->name = roomName;
        lobbyMap->insert((std::pair<string, GameroomData *>(roomName, roomData)));
        //send numbers to the players
        sendToClient(clientSocket1, "1");
        sendToClient(clientSocket2, "2");
        cout << "Successfully joined game players " << clientSocket1 << " and " << clientSocket2 << endl;
    } else {
        sendToClient(clientSocket2, FAILURE);
    }
}

void JoinCommand::sendToClient(int clientSocket, string message) const {
    char buffer;
    int i = 0, n;
    while (i < message.length()) {
        buffer = message.at(i);
        n = write(clientSocket, &buffer, sizeof(char));
        if (ERROR == n) throw "Error sending message";
        i++;
    }
    buffer = '\0';
    n = write(clientSocket, &buffer, sizeof(char));
    if (ERROR == n) throw "Error sending message";
}