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
    /**
     * The method check if the thread need to be done
     * @return bool
     */
    static bool threadIsDone(string command);

    /**
     * The method check if need to start run a game
     * @return bool
     */
    static bool startRunningGame(string command, vector<string> args, CommandsManager *manager);

    /**
     * The game running sending message
     */
    static void runGame(GameroomData *roomData, Server *server);

    /**
     * The method read from socket1 and write to socket2
     * @return CONTINUE if should be to continue, and END if should be end the game
     */
    static int playOneTurn(int socket1, int socket2, Server *server, string roomName);

public:

    static void *handleClient(void *clientData);

    static void swapSockets(int *clientSocket1, int *clientSocket2);

    static bool shouldDeleteClientData(string command);
};


#endif //TCPSERVER_HANDLECLIENT_H
