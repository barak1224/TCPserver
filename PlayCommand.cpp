/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "PlayCommand.h"

void PlayCommand::execute(vector<string> args, int clientSocket1, int clientSocket2) {
    char buffer;
    int n;
    try {
        //TODO CHECK INPUT if it is legal
        if (strcmp("noMove", args[0].c_str()) == 0) {
            sendToClient(clientSocket2, args[0]);
        } else {
            string message = args[0] + ' ' + args[1];
            sendToClient(clientSocket2, message);

        }
    } catch (...) {
        return;
    }
}


void PlayCommand::sendToClient(int clientSocket, string message) const {
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