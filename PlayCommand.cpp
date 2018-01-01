/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "PlayCommand.h"

void PlayCommand::execute(vector<string> args, int clientSocket1, int clientSocket2) {
    //TODO CHECK INPUT if it is legal
    sendToClient(clientSocket2, args[0]);
}


void PlayCommand::sendToClient(int clientSocket, string message) const {
    char buffer;
    int i = 0, n;
    while (i < message.length()) {
        buffer = message.at(i);
        n = write(clientSocket, &buffer, sizeof(char));
        cout << "writing " << buffer << endl;
        if (ERROR == n) throw "Error sending message";
        i++;
    }
    buffer = '\0';
    n = write(clientSocket, &buffer, sizeof(char));
    if (ERROR == n) throw "Error sending message";
}