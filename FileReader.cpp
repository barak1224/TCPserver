#include "FileReader.h"

int FileReader::readPort(string s) {
    int port;
    ifstream inFile;
    inFile.open(s.c_str());
    inFile >> port;
    inFile.close();
    return port;
}

