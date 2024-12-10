#include "UDPSocket.h"
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]){
    struct sockaddr_in si_other;
    int slen = sizeof(si_other);

    char buf[BUFLEN];
    char message[BUFLEN];

    unsigned short srv_port = PORT;
    char srv_ip_addr[40] = SERVER;

    UDPSocket client_sock;

    memset((char*)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;

    if(argc == 1){
        si_other.sin_port = htons(PORT);
        si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
        cout<<"Default Server addr="<<SERVER<<" port="<<PORT<<endl;
    }else if(argc == 2){
        si_other.sin_port = htons(atoi(argv[1]));
        si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
        cout<<"Server addr="<<SERVER<<" port="<<atoi(argv[1])<<endl;
    }else{
        si_other.sin_port = htons(atoi(argv[2]));
        si_other.sin_addr.S_un.S_addr = inet_addr(argv[1]);
        cout<<"Server addr="<<argv[1]<<" port="<<atoi(argv[2])<<endl;
    }

    while(true){
        cout<<"\nEnter message: ";
        cin.getline(message, BUFLEN);

        client_sock.SendDatagram(message, strlen(message), (struct sockaddr*)&si_other, slen);

        memset(buf, '\0', BUFLEN);
        client_sock.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);

        cout<<"Server reply "<<buf<<endl;
    }
}