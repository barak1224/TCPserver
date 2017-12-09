#include "FileReader.h"

int FileReader::readPort(string s) {
    int port;
    ifstream inFile;
    inFile.open("user.txt");
    inFile >> port;
    inFile.close();
    return port;
}

