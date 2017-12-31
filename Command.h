`/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_COMMAND_H
#define TCPSERVER_COMMAND_H


#define  SUCCESS "success"
#define  FAILURE "failure"


#include <string>
#include "Server.h"

using namespace std;

/**
 * Command interface, to be in charge
 */

class Command {
private:
    virtual void sendToClient(int clientSocket, string message) const = 0;

public:
    virtual void execute(vector<string> args, struct ClientData *data) = 0;

    virtual ~Command() {}
};

#endif //TCPSERVER_COMMAND_H
