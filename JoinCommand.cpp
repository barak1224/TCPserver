/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#define START "start"

#include "JoinCommand.h"

JoinCommand::JoinCommand(map<string, int> *openGames, map<string, GameroomData *> *lobbyMap) : openGames(openGames),
                                                                                             lobbyMap(lobbyMap) {}

void JoinCommand::execute(vector<string> args, int clientSocket2, int clientSocketSpare) {
    string roomName = args[0];
    if (openGames->find(roomName) != openGames->end()) {    //success in finding the room
        cout << "Client is connecting to room " + roomName << endl;
        int clientSocket1 = (*openGames)[roomName];
        GameroomData *roomData = new GameroomData();
        roomData->socket1 = clientSocket1;
        roomData->socket2 = clientSocket2;
        roomData->name = roomName;
        lobbyMap->insert((std::pair<string, GameroomData *>(roomName, roomData)));
//        (*lobbyMap)[roomName] = roomData;
        cout << "Successfully joined game players " << clientSocket1 << " and " << clientSocket2 << endl;
        openGames->erase(roomName);
        //send numbers to the players
        sendToClient(clientSocket1, "1");
        sendToClient(clientSocket2, "2");

    } else {                                                //failed finding the room
        sendToClient(clientSocket2, FAILURE);
    }
}

void JoinCommand::sendToClient(int clientSocket, string message) const {
    char *convert = new char[MAX_LENGTH];
    memset(convert, 0, MAX_LENGTH);
    strcpy(convert, message.c_str());
    int n = write(clientSocket, &message, sizeof(message));
    delete convert;
    if (n == ERROR)
        throw "Error writing to client " + message;
}