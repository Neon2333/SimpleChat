/*
*Author:wk
*Date:2024/8/22
*Description: the class for tcp server encapsulation
*/

#ifndef TCPSERVER_H
#define TCPSERVER_H
#include "Tcplib.h"

class TcpServer
{
private:
    struct sockaddr_in m_server_addr;
    struct sockaddr_in m_client_addr;
    int m_client_addr_size;
public:
    unsigned int m_port;   
    int m_listenfd;
    int m_clientfd;
    bool m_btimeout;
    int m_bufferlen;
public:
    TcpServer();
    ~TcpServer();
    bool InitServer(const unsigned int port, const int maxclientfd=1000);
    bool Accept();

    bool Read(char* buffer, const int timeout=0);
    bool Write(char* buffer, int ibuflen=0);
    char* GetIP();
    void CloseListen(); 
    void CloseClient();
};

#endif