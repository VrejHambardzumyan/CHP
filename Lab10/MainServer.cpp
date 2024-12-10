#include "UDPServer.h"
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]){
    struct sockaddr_in si_other;
    unsigned short srvport = (argc == 1) ? PORT : atoi(argv[1]);

    UDPServer server(srvport);
    int slen = sizeof(si_other);

    char buf[BUFLEN];
    char msg[BUFLEN];

    while(true){
        cout<<"Waiting for data...\n";

        memset(buf, '\0', BUFLEN);

        server.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);
        cout<<"Received packet from "<<inet_ntoa(si_other.sin_addr)
                  <<":"<<ntohs(si_other.sin_port)<<"\nData "<<buf<<endl;

        cout<<"\nEnter reply ";
        cin.getline(msg, BUFLEN);

        server.SendDatagram(msg, strlen(msg), (struct sockaddr*)&si_other, slen);
    }
}