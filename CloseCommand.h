/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_CLOSECOMMAND_H
#define TCPSERVER_CLOSECOMMAND_H


#include "Command.h"

class CloseCommand : public Command {
private:
    pthread_mutex_t *lobbyMapLock;
    map<string, GameroomData *> *lobbyMap;
    map<string, int> *openGames;
    virtual void sendToClient(int clientSocket, string message) const;
public:
    CloseCommand(map<string, GameroomData *> *lobbyMap, pthread_mutex_t *lobbyMapLock);
    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2);
    virtual ~CloseCommand() {}
};


#endif //TCPSERVER_CLOSECOMMAND_H
