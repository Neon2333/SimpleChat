/*
*Author:wk
*Date:2024/8/22
*Description: the class for forwarding message
*/

#ifndef FORWARD_HPP
#define FORWARD_HPP
#include "Client.hpp"
#include "Tcplib.h"


bool sendMsgToAllClientsBut(Client** clients, int numclients, int excluded, char *s);
//forward to all
bool forw000(char* strSendBuffer, Client** clients, int sizeClients, int clientfd)
{
    return true;
}

//forward to all but one
bool forw001(char* strSendBuffer, Client** clients, int sizeClients, int clientfd)
{
    return sendMsgToAllClientsBut(clients, sizeClients, clientfd, strSendBuffer);
}

//forward to one 
bool forw002(char* strSendBuffer, Client** clients, int sizeClients, int clientfd)
{
    return true;
}

bool sendMsgToAllClientsBut(Client** clients, int sizeclients, int excluded, char *s) 
{
    bool ret=true;
    for (int j = 0; j <sizeclients; j++) 
    {
        if (clients[j] == NULL ||
            clients[j]->m_clientfd == excluded) continue;

        //判断sockfd是否可写
	    fd_set tmpfd;
		FD_ZERO(&tmpfd);
		FD_SET(clients[j]->m_clientfd,&tmpfd);
		if(select(clients[j]->m_clientfd+1,0,&tmpfd,0,0)<0)
		{
			continue;
		}

        if(false==TcpWrite(clients[j]->m_clientfd, s))
		{
			close(clients[j]->m_clientfd);
            ret=false;
            continue;
        }
                
    }
    return ret;
}

#endif