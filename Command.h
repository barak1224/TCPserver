/**
 * Created by Josef Ginerman on 25/12/17.
 **/

#ifndef TCPSERVER_COMMAND_H
#define TCPSERVER_COMMAND_H

#include <vector>
#include <string>

using namespace std;
/**
 * Command interface, to be in charge
 */
class Command {
public:
    virtual void execute(vector<string> args) = 0;
    virtual ~Command() {}
};


#endif //TCPSERVER_COMMAND_H
