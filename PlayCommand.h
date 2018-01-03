/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_PLAYCOMMAND_H
#define TCPSERVER_PLAYCOMMAND_H


#include <map>
#include "Command.h"
#include "GameroomData.h"

class PlayCommand : public Command {
private:
    map<string, GameroomData> *lobbyMap;
    map<string, int> *openGames;
    /**
     * The method send the play move to the second player
     */
    virtual void sendToClient(int clientSocket, string message) const;
public:
    /**
     * The method parsing the args into a string and send to the sendToClient method
     */
    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2);
    /**
     * Constructor
     */
    PlayCommand() {}
    /**
     * Destructor
     */
    virtual ~PlayCommand() {}
};


#endif //TCPSERVER_PLAYCOMMAND_H
