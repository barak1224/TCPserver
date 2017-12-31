/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#include "PrintCommand.h"

PrintCommand::PrintCommand(map<string, int> *openGames) : openGames(openGames) {}

void PrintCommand::execute(vector<string> args, int clientSocket) {
    string result = "";
    if (!openGames->empty()) {
        result = "List of Games:\n";
        string next = " ";
        for (std::map<string, int>::iterator it = openGames->begin(); it != openGames->end(); ++it) {
            next.append("\t" + it->first + "\n");
            result.append(next);
        }
    } else {
        result = "There are no open games\n";
    }
    sendToClient(clientSocket, result);
    // the client only wanted to print, so the socket is closed now
    close(clientSocket);
}



void PrintCommand::sendToClient(int clientSocket, string message) const {
    int n = write(clientSocket, &message, sizeof(message));
    if (n == ERROR)
        throw "Error writing to client " + message;
}