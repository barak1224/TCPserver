/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_EXITCOMMAND_H
#define TCPSERVER_EXITCOMMAND_H


#include "Command.h"

class StartCommand : public Command {
public:
    StartCommand(map<string, int> *openGames, pthread_mutex_t *openGamesLock);
    /**
     * The method make new member in the openGame map which the key is the room name
     * and the value is the socketClient of the client that open the room
     */
    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2);
    /**
     * The destructor
     */
    virtual ~StartCommand() {}
    /**
     * The Constructor
     */
    StartCommand() {}

private:
    pthread_mutex_t *openGamesLock;
    map<string, int> *openGames;
    /**
     * Send a message if the open game was failed
     */
    void sendToClient(int clientSocket, string message) const;
};


#endif //TCPSERVER_EXITCOMMAND_H
