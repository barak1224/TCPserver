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
    /**
     * Sending the socket client a message
     */
    virtual void sendToClient(int clientSocket, string message) const = 0;

public:
    /**
     * The execute method
     */
    virtual void execute(vector<string> args, int clientSocket1, int clientSocket2) = 0;

    /**
     * Destructor
     */
    virtual ~Command() {}
};

#endif //TCPSERVER_COMMAND_H
