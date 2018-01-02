/**
 * Created by Josef Ginerman on 29/12/17.
 **/

#ifndef TCPSERVER_HANDLECLIENT_H
#define TCPSERVER_HANDLECLIENT_H

#define END false
#define CONTINUE true

#include "Server.h"


class Server;

class ClientHandler {
private:

    static bool threadIsDone(string command);

    static bool startRunningGame(string command, vector<string> args, CommandsManager *manager);

    static void runGame(GameroomData *roomData, Server *server);

    static int playOneTurn(int socket1, int socket2, Server *server, string basicString);

public:

    static void *handleClient(void *clientData);

//    string getCommand(char *message);
//
//    vector<string> getArgs(char *buffer);

    static void swapSockets(int *clientSocket1, int *clientSocket2);

    static bool shouldDeleteClientData(string command);
};


#endif //TCPSERVER_HANDLECLIENT_H
