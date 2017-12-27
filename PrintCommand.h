/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_PRINTCOMMAND_H
#define TCPSERVER_PRINTCOMMAND_H


#include <map>
#include "Command.h"

class PrintCommand : public Command {
private:
    map<string, int> openGames;
public:
    PrintCommand(map<string, int> openGames);
    virtual void execute(vector<string> args);
    virtual ~PrintCommand() {}
};


#endif //TCPSERVER_PRINTCOMMAND_H
