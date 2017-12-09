#ifndef TCPSERVER_FILEREADER_H
#define TCPSERVER_FILEREADER_H

#include <iostream>
#include <fstream>

using namespace std;

class FileReader {
public:
    FileReader() {}
    /**
     * The method reading from a file the port
     * @return port of the server
     */
    int readPort(string s);
};


#endif //TCPSERVER_FILEREADER_H
