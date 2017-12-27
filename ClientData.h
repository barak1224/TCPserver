/**
 * Created by Josef Ginerman on 27/12/17.
 **/

#ifndef TCPSERVER_CLIENTDATA_H
#define TCPSERVER_CLIENTDATA_H

struct ClientData {
    int clientSocket;
    Server *server;
    pthread_t *threadID;
};

#endif //TCPSERVER_CLIENTDATA_H
