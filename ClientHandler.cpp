/**
 * Created by Josef Ginerman on 29/12/17.
 **/

#include <cstdlib>
#include "ClientHandler.h"

void getCommand(string buffer, string *command);

void getArgs(string commandStr, vector<string> *args);

void *ClientHandler::handleClient(void *clientData) {
    cout << "I am here" << endl;
    struct ClientData *data = (struct ClientData *) clientData;
    Server *server = data->server;
    int clientSocket1 = data->clientSocket;
    CommandsManager *manager = server->getCommandsManager();

    string buffer;
    int n = server->readFrom(clientSocket1, buffer);
    // get the commands
    string command;
    getCommand(buffer, &command);
    vector<string> args;
    getArgs(buffer, &args);

    manager->executeCommand(command, args, clientSocket1);

    // start running the game inside the join-command's thread
    if (startRunningGame(command, args, manager)) {
        manager->getOpenGames()->erase(args[0]);
        GameroomData *roomData = (*manager->getLobbyMap())[args[0]];
        runGame(roomData, server);
    }
}

bool ClientHandler::startRunningGame(string command, vector<string> args, CommandsManager *manager) {
    return (strcmp("join", command.c_str()) == 0 &&
            manager->getOpenGames()->find(args[0]) != manager->getOpenGames()->end());
}

void ClientHandler::runGame(GameroomData *roomData, Server *server) {
    int clientSocket1 = roomData->socket1;
    int clientSocket2 = roomData->socket2;
    string roomName = roomData->name;

    // the actual sending messages from one player to the other
    bool playNext = CONTINUE;
    while (playNext) {
        playNext = playOneTurn(clientSocket1, clientSocket2, server, roomName);
        swapSockets(&clientSocket1, &clientSocket2);
    }
    server->getCommandsManager()->getLobbyMap()->erase(roomName);
    close(clientSocket1);
    close(clientSocket2);
    delete roomData;
}


int ClientHandler::playOneTurn(int socket1, int socket2, Server *server, string roomName) {
    CommandsManager *manager = server->getCommandsManager();
    string message = "";
    if (server->readFrom(socket1, message)) {
        if (strcmp("close", message.c_str()) == 0) {
            return END;
        }
        string command;
        getCommand(message, &command);
        vector<string> args;
        getArgs(message, &args);
        if (strcmp(command.c_str(), "close") == 0) {
            args.push_back(roomName);
        }

        manager->executeCommand(command, args, socket1, socket2);

        if (strcmp("close", command.c_str()) == 0)
            return END;
        if (strcmp("play", command.c_str()) == 0)
            return CONTINUE;
    } else return ERROR;
}

void getCommand(string buffer, string *command) {
    *command = buffer.substr(0, buffer.find(" "));
}

void getArgs(string commandStr, vector<string> *args) {
    if (commandStr.find(" ") == ERROR) {
        args->push_back("");
        return;
    }
    // get the commands
    commandStr = commandStr.substr(commandStr.find(" "));
    char *commandChar = new char[MAX_LENGTH];
    strcpy(commandChar, commandStr.c_str());
    string separators = " ";
    char *tok = strtok(commandChar, separators.c_str());
    while (tok != NULL) {
        args->push_back(tok);
        tok = strtok(NULL, separators.c_str());
    }
}

void ClientHandler::swapSockets(int *clientSocket1, int *clientSocket2) {
    int temp = *clientSocket1;
    *clientSocket1 = *clientSocket2;
    *clientSocket2 = temp;
}