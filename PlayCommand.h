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
public:
    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2);
    virtual ~PlayCommand() {}

    void sendToClient(int clientSocket, string message) const;
};


#endif //TCPSERVER_PLAYCOMMAND_H
