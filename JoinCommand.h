/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_JOINCOMMAND_H
#define TCPSERVER_JOINCOMMAND_H


#include "Command.h"

class JoinCommand : public Command {
public:
    virtual void execute(vector<string> args);
    virtual ~JoinCommand() {}
};


#endif //TCPSERVER_JOINCOMMAND_H
