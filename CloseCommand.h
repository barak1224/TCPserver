/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_CLOSECOMMAND_H
#define TCPSERVER_CLOSECOMMAND_H


#include "Command.h"

class CloseCommand : public Command {
private:
    map<string, GameroomData> *lobbyMap;
    map<string, int> *openGames;
    virtual void sendToClient(int clientSocket, string message) const;
public:
    CloseCommand(map<string, int> *openGames, map<string, GameroomData> *lobbyMap);
    virtual void execute(vector<string> args, int clientSocket);
    virtual ~CloseCommand() {}
};


#endif //TCPSERVER_CLOSECOMMAND_H
