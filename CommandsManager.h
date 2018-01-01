/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_COMMANDMANAGER_H
#define TCPSERVER_COMMANDMANAGER_H

#define ERROR -1

#include "Command.h"
#include "GameroomData.h"

#include <vector>
#include <map>


class CommandsManager {

public:
    CommandsManager();

    ~CommandsManager();

    void executeCommand(string command, vector<string> args, int clientSocket1, int clientSocket2 = 0);

    map<string, GameroomData>* getLobbyMap() { return this->lobbyMap; }
    map<string, int>* getOpenGames() { return this->openGames; }

private:
    map<string, Command *> commandsMap;
    map<string, GameroomData> *lobbyMap;
    map<string, int> *openGames;
};

#endif //TCPSERVER_COMMANDMANAGER_H
