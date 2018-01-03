/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_PRINTCOMMAND_H
#define TCPSERVER_PRINTCOMMAND_H


#include <map>
#include "Command.h"

#define MAX_LENGTH 30

class PrintCommand : public Command {
private:
    pthread_mutex_t *openGamesLock;
    map<string, int> *openGames;
    virtual void sendToClient(int clientSocket, string message) const;
public:
    PrintCommand(map<string, int> *openGames, pthread_mutex_t *openGamesLock);
    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2);
    virtual ~PrintCommand() {}
};


#endif //TCPSERVER_PRINTCOMMAND_H
