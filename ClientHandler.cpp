/**
 * Created by Josef Ginerman on 29/12/17.
 **/

#include "ClientHandler.h"


void *ClientHandler::handleClient(void *clientData) {
    struct ClientData *data = (struct ClientData *) clientData;
    Server *server = data->server;
    int clientSocket1 = data->clientSocket;
    CommandsManager *manager = server->getCommandsManager();


    char buffer[MAX_LENGTH];
    int n = read(clientSocket1, buffer, MAX_LENGTH);
    // get the commands
    string command = getCommand(buffer);
    vector<string> args = getArgs(buffer);

    manager->executeCommand(command, args, clientSocket1);

    if (startRunningGame(command, args, manager)) {
        GameroomData roomData = (*manager->getLobbyMap())[args[0]];
        runGame(roomData, server);
    }
    if (threadIsDone(command)) {
        //TODO
    }
}


bool ClientHandler::threadIsDone(string command) {
    return (strcmp("start", command.c_str()) == 0 || strcmp("list_games", command.c_str()) == 0);
}

bool ClientHandler::startRunningGame(string command, vector<string> args, CommandsManager *manager) {
    if (strcmp("join", command.c_str()) != 0)
        return false;
    string roomName = args[0];
    map<string, GameroomData> *lobbyMap = manager->getLobbyMap();
    {
        return lobbyMap->find(roomName) != lobbyMap->end();
    }
}


void ClientHandler::runGame(GameroomData roomData, Server *server) {
    int clientSocket1 = roomData.socket1;
    int clientSocket2 = roomData.socket2;
    string roomName = roomData.name;

    // the actual sending messages from one player to the other
    bool playNext = CONTINUE;
    while (playNext) {
        playNext = playOneTurn(clientSocket1, clientSocket2, server);
        swapSockets(&clientSocket1, &clientSocket2);
    }
    close(clientSocket1);
    close(clientSocket2);
}

int ClientHandler::playOneTurn(int socket1, int socket2, Server *server) {
    pthread_mutex_t play_mutex;
    CommandsManager *manager = server->getCommandsManager();
    char *message = NULL;
    if (server->readFrom(socket1, message)) {
        string command = getCommand(message);
        vector<string> args = getArgs(message);

        pthread_mutex_lock(&play_mutex);
        manager->executeCommand(command, args, socket1, socket2);
        pthread_mutex_unlock(&play_mutex);

        if (strcmp("close", command.c_str()) == 0)
            return END;
        if (strcmp("play", command.c_str()) == 0)
            return CONTINUE;
    }
}

string ClientHandler::getCommand(char *buffer) {
    string commandStr(buffer);
    string command = commandStr.substr(0, commandStr.find(" "));
    return command;
}


vector<string> ClientHandler::getArgs(char *buffer) {
    // get the commands
    string commandStr(buffer);
    commandStr = commandStr.substr(commandStr.find(" "));
    char *commandChar = NULL;
    strcpy(commandChar, commandStr.c_str());
    vector<string> args;
    string separators = " ";
    char *tok = strtok(commandChar, separators.c_str());
    while (tok != NULL) {
        args.push_back(tok);
        tok = strtok(NULL, separators.c_str());
    }
    return args;
}


void ClientHandler::swapSockets(int *clientSocket1, int *clientSocket2) {
    int *temp = clientSocket1;
    clientSocket1 = clientSocket2;
    clientSocket2 = temp;
}