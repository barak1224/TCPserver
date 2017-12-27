/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_PLAYCOMMAND_H
#define TCPSERVER_PLAYCOMMAND_H


#include "Command.h"

class PlayCommand : public Command {
public:
    virtual void execute(vector<string> args);
    virtual ~PlayCommand() {}
};


#endif //TCPSERVER_PLAYCOMMAND_H
