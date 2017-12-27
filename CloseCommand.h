/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_CLOSECOMMAND_H
#define TCPSERVER_CLOSECOMMAND_H


#include "Command.h"

class CloseCommand : public Command {
public:
    virtual void execute(vector<string> args);
    virtual ~CloseCommand() {}
};


#endif //TCPSERVER_CLOSECOMMAND_H
