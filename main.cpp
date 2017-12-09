#include "Server.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
int main() {
    Server server(8001);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}