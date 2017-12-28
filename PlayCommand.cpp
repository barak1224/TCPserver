/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "PlayCommand.h"

void PlayCommand::execute(vector<string> args, int clientSocket) {
    string moveCoordinates = args[0];
}



void PlayCommand::sendToClient(int clientSocket, string message) const {
    int n = write(clientSocket, &message, sizeof(message));
    if (n == ERROR)
        throw "Error writing to client " + message;
}