/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_EXITCOMMAND_H
#define TCPSERVER_EXITCOMMAND_H


#include "Command.h"

class StartCommand : public Command {
public:
    virtual void execute(vector<string> args);
    virtual ~StartCommand() {}
};


#endif //TCPSERVER_EXITCOMMAND_H
