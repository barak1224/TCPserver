/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_COMMAND_H
#define TCPSERVER_COMMAND_H


#define  SUCCESS "success"
#define  FAILURE "failure"
#define ERROR -1


#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include "GameroomData.h"

/**
 * Command interface, to be in charge
 */

using namespace std;

class Command {
private:
    virtual void sendToClient(int clientSocket, string message) const = 0;

public:
    virtual void execute(vector<string> args, int clientSocket) = 0;

    virtual ~Command() {}
};

#endif //TCPSERVER_COMMAND_H
