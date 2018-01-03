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
    /**
     * The method send to the client socket the last move before closing the room
     */
    virtual void sendToClient(int clientSocket, string message) const;
public:
    /**
     * Constructor
     */
    CloseCommand(map<string, GameroomData *> *lobbyMap, pthread_mutex_t *lobbyMapLock);
    /**
     * The method executing the command
     */
    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2);
    /**
     * The destructor
     */
    virtual ~CloseCommand() {}
};


#endif //TCPSERVER_CLOSECOMMAND_H
