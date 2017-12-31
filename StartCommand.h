/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_EXITCOMMAND_H
#define TCPSERVER_EXITCOMMAND_H


#include "Command.h"

class StartCommand : public Command {
public:
    StartCommand(map<string, int> *openGames);
    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2);
    virtual ~StartCommand() {}

private:
    map<string, int> *openGames;
    void sendToClient(int clientSocket, string message) const;
};


#endif //TCPSERVER_EXITCOMMAND_H
