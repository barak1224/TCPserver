/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "StartCommand.h"

StartCommand::StartCommand(map<string, int> *openGames, pthread_mutex_t *openGamesLock) : openGames(openGames), openGamesLock(openGamesLock) {}

void StartCommand::execute(vector<string> args, int clientSocket1, int clientSocket2) {
    // args[0] is the name of the created game
    string roomName = args[0];
    if (openGames->find(roomName) != openGames->end()) {
        string message = FAILURE;
        sendToClient(clientSocket1, message);
    } else {
        cout << "Client " << clientSocket1 << " opened game " << roomName << endl;
        pthread_mutex_lock(openGamesLock);
        (*openGames)[roomName] = clientSocket1;
        pthread_mutex_unlock(openGamesLock);
    }
}

void StartCommand::sendToClient(int clientSocket, string message) const {
    char buffer;
    int i = 0, n;
    while (i < message.length()) {
        buffer = message.at(i);
        n = write(clientSocket, &buffer, sizeof(char));
        if (ERROR == n) throw "Error reading";
        i++;
    }
    buffer = '\0';
    n = write(clientSocket, &buffer, sizeof(char));
    if (ERROR == n) throw "Error reading";
}