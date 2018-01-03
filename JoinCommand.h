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
    /**
     * The method send to the client socket his number before starting the game
     */
    virtual void sendToClient(int clientSocket, string message) const;

public:
    /**
     * Constructor
     */
    JoinCommand(map<string, int> *openGames, map<string, GameroomData *> *lobbyMap, pthread_mutex_t *openGamesLock,
                pthread_mutex_t *lobbyMapLock);

    /**
     * The method executing the command
     */
    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2);
    /**
     * The destructor
     */
    virtual ~JoinCommand() {}
};


#endif //TCPSERVER_JOINCOMMAND_H
