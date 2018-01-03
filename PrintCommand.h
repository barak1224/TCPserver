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
    /**
     * Constructor
     */
    PrintCommand(map<string, int> *openGames, pthread_mutex_t *openGamesLock);
    /**
     * The method parsing the names of the open rooms into string and send it to sendToClient method
     */
    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2);
    /**
     * The destructor
     */
    virtual ~PrintCommand() {}
};


#endif //TCPSERVER_PRINTCOMMAND_H
