/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_JOINCOMMAND_H
#define TCPSERVER_JOINCOMMAND_H


#include "Command.h"

class JoinCommand : public Command {

private:
    pthread_mutex_t *openGamesLock;
    pthread_mutex_t *lobbyMapLock;
    map<string, GameroomData *> *lobbyMap;
    map<string, int> *openGames;

    virtual void sendToClient(int clientSocket, string message) const;

public:
    JoinCommand(map<string, int> *openGames, map<string, GameroomData *> *lobbyMap, pthread_mutex_t *openGamesLock,
                pthread_mutex_t *lobbyMapLock);

    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2);

    virtual ~JoinCommand() {}

    void readFrom(int clientSocket, string &message);
};


#endif //TCPSERVER_JOINCOMMAND_H
