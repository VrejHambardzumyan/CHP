#include "UDPServer.h"
#include <iostream>
#include <cstdlib>

using namespace std;

UDPServer::UDPServer(unsigned short serverport) : UDPSocket(), mServerPort(serverport){
    mServer.sin_family = AF_INET;
    mServer.sin_addr.s_addr = INADDR_ANY;
    mServer.sin_port = htons(mServerPort);

    if (bind(s, (struct sockaddr*)&mServer, sizeof(mServer)) == SOCKET_ERROR) {
        cerr<<"Bind failed "<<WSAGetLastError()<<endl;
        exit(EXIT_FAILURE);
    }
}

UDPServer::~UDPServer() {}