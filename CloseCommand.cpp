/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "CloseCommand.h"

CloseCommand::CloseCommand(map<string, GameroomData *> *lobbyMap,
                           pthread_mutex_t *lobbyMapLock) : lobbyMap(lobbyMap), lobbyMapLock(lobbyMapLock) {}

void CloseCommand::execute(vector<string> args, int clientSocket1, int clientSocket2) {
    string roomName = args[2];
    // if the game is not in the lobby
    if (lobbyMap->find(roomName) == lobbyMap->end()) {
        sendToClient(clientSocket1, FAILURE);
    } else {
        string message = args[0] + " " + args[1];
        pthread_mutex_lock(lobbyMapLock);
        GameroomData *roomData = (*lobbyMap)[roomName];
        pthread_mutex_unlock(lobbyMapLock);
        // tell the second client the game is closing
        if (clientSocket1 == roomData->socket1) {
            sendToClient(roomData->socket2, message.c_str());
        } else if (clientSocket1 == roomData->socket2) {
            sendToClient(roomData->socket1, message.c_str());
        }
    }
}


void CloseCommand::sendToClient(int clientSocket, string message) const {
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