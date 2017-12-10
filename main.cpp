#include "Server.h"
#include "FileReader.h"
#include <stdlib.h>

using namespace std;
int main() {
    FileReader file;
    Server server(file.readPort("ServerPort.txt"));
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}