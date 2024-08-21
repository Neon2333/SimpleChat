/*
*Author:wk
*Date:2024/8/22
*Description: the class for tcp server encapsulation
*/

#include "TcpServer.h"

TcpServer::TcpServer()
{
    m_port=-1;
    m_listenfd=-1;
    m_client_addr_size=0;
    m_bufferlen=0;
    m_btimeout=false;	//Read/Write是否是因为超时而返回false，超时为true
}

TcpServer::~TcpServer()
{
    CloseListen();
    CloseClient();
}

bool TcpServer::InitServer(const unsigned int port, const int maxclientsfd)
{
    if(m_listenfd>0)
    {
        close(m_listenfd);
        m_listenfd=-1;
    }
	
    m_listenfd = socket(PF_INET, SOCK_STREAM, 0);
    
    if(m_listenfd == -1) return false;


    int opt=1;
    unsigned int len=sizeof(opt);
    setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, len);
	
	
    memset(&m_server_addr, 0, sizeof(m_server_addr));
    m_server_addr.sin_family=AF_INET;
    m_server_addr.sin_addr.s_addr=htonl(INADDR_ANY);	
    m_server_addr.sin_port=htons(port);

    if(bind(m_listenfd, (struct sockaddr*) &m_server_addr, sizeof(m_server_addr)) == -1)
    {
        CloseListen();
        return false;
    }
    
    if(listen(m_listenfd, 511) == -1)
    {
        CloseListen();
        return false;
    }

    return true;
}

bool TcpServer::Accept()
{
    if(m_listenfd == -1)   
        return false;
    m_client_addr_size=sizeof(m_client_addr);
    if((m_clientfd = accept(m_listenfd, (struct sockaddr*)&m_client_addr,(socklen_t*)&m_client_addr_size)) == -1)
        return false;
    
    return true;
}

bool TcpServer::Read(char* buffer, const int timeout)
{
    if(m_clientfd==-1)	
        return false;	   
    if(timeout>0)
    {
        fd_set tmpfd;
    
    	FD_ZERO(&tmpfd);
    	FD_SET(m_clientfd,&tmpfd);
    
    	struct timeval sttimeout;
    	sttimeout.tv_sec=timeout;
    	sttimeout.tv_usec=0;
        m_btimeout=false;

        int i; 
        if((i=select(m_clientfd+1,&tmpfd,0,0,&sttimeout))<=0)	
    	{
        	if(i==0)
            	m_btimeout=true;
        	return false;
    	}
    }
    m_bufferlen=0;
    return TcpRead(m_clientfd, buffer, &m_bufferlen);
}


bool TcpServer::Write(char* buffer, int ibuflen)
{
    if(m_clientfd==-1)	return false;
    
    fd_set tmpfd;
    
    FD_ZERO(&tmpfd);
    FD_SET(m_clientfd,&tmpfd);
    
    struct timeval sttimeout;
    sttimeout.tv_sec=5;
    sttimeout.tv_usec=0;
    
    int i;
    if((i=select(m_clientfd+1,0,&tmpfd,0,&sttimeout))<=0)	
    {
        if(i==0)
            m_btimeout=true;
        return false;
    }
    int ilen=ibuflen;
    if(ilen==0)
        ilen=strlen(buffer);
    
    return TcpWrite(m_clientfd, buffer, &ilen);
}
    
char* TcpServer::GetIP()
{
    return inet_ntoa(m_client_addr.sin_addr);
}
    
void TcpServer::CloseListen()
{
    close(m_listenfd);
    m_listenfd=-1;
}

void TcpServer::CloseClient()
{
    close(m_clientfd);
    m_clientfd=-1;
}

