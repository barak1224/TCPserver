/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_COMMANDMANAGER_H
#define TCPSERVER_COMMANDMANAGER_H

#include <map>
#include "Command.h"
#include "Server.h"


class CommandsManager {
public:
    CommandsManager(Server* server);
    ~CommandsManager();
    void executeCommand(string command, vector<string> args);
    struct GameroomData {
        int socket1;
        int socket2;
        //TODO maybe something more?
    };
    Server *getServer() { return this->server;}
private:
    Server *server;
    map<string, Command *> commandsMap;
    map<string, GameroomData> lobbyMap;
    map<string, int> openGames;
};

#endif //TCPSERVER_COMMANDMANAGER_H
