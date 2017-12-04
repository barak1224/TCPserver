/**
 * Created by Josef Ginerman on 04/12/17.
 * ID : 332494830
 **/

#ifndef TCPSERVER_SERVER_H
#define TCPSERVER_SERVER_H


class Server {
public:
    Server(int port);
    void start();
    void stop();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    void handleClient(int clientSocket);
    int calc(int arg1, const char op, int arg2) const;
};

#endif //TCPSERVER_SERVER_H
