/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "PrintCommand.h"

PrintCommand::PrintCommand(map<string, int> *openGames, pthread_mutex_t *openGamesLock) : openGames(openGames),
                                                                                          openGamesLock(
                                                                                                  openGamesLock) {}

void PrintCommand::execute(vector<string> args, int clientSocket1, int clientSocket2) {
    string result = "";
    pthread_mutex_lock(openGamesLock);
    bool empty = openGames->empty();
    pthread_mutex_unlock(openGamesLock);

    if (!empty) {
        result = "List of Games:\n";

        pthread_mutex_lock(openGamesLock);
        for (std::map<string, int>::iterator it = openGames->begin(); it != openGames->end(); ++it) {
            result.append("\t" + it->first + "\n");
        }
        pthread_mutex_unlock(openGamesLock);

    } else {
        result = "There are no open games\n";
    }
    sendToClient(clientSocket1, result);
    // the client only wanted to print, so the socket is closed now
    close(clientSocket1);
}


void PrintCommand::sendToClient(int clientSocket, string message) const {
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