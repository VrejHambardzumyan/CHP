#include "UDPSocket.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int UDPSocket::WSAInit(){
    static unsigned int count = 0;
    if(count++) return 0;
#ifdef _WIN32
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        cerr<<"WSAStartup failed "<<WSAGetLastError()<<endl;
        exit(EXIT_FAILURE);
    }
#endif
    return 0;
}

UDPSocket::UDPSocket(){
    UDPSocket::WSAInit();
    if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR){
        cerr<< "Socket creation failed "<<WSAGetLastError()<<endl;
        exit(EXIT_FAILURE);
    }
}

UDPSocket::~UDPSocket(){
#ifdef _WIN32
    closesocket(s);
    WSACleanup();
#endif
}

int UDPSocket::SendDatagram(char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen){
    if(sendto(s, msg, msglen, 0, si_dest, slen) == SOCKET_ERROR){
        cerr<<"sendto() failed "<<WSAGetLastError()<<endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}

int UDPSocket::RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int* slen) {
    if(recvfrom(s, buf, buflen, 0, si_dest, slen) == SOCKET_ERROR){
        cerr<<"recvfrom() failed "<< WSAGetLastError()<<endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}