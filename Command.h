/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_COMMAND_H
#define TCPSERVER_COMMAND_H

#define DISCONNECT 0
#define MAX_LENGTH 30
#define  FAILURE "-1"
#define ERROR -1

#include <cstring>
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
    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2) = 0;

    virtual ~Command() {}
};

#endif //TCPSERVER_COMMAND_H
