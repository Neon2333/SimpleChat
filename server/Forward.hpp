#ifndef FORWARD_HPP
#define FORWARD_HPP
#include "Client.hpp"
#include "Tcplib.h"


bool sendMsgToAllClientsBut(Client** clients, int numclients, int excluded, char *s);
//forward to one
bool forw000(char* strSendBuffer, Client** clients, int sizeClients, int clientfd)
{
    return true;
}

//forward to anyone but one
bool forw001(char* strSendBuffer, Client** clients, int sizeClients, int clientfd)
{
    return sendMsgToAllClientsBut(clients, sizeClients, clientfd, strSendBuffer);
}

//forward to all 
bool forw002(char* strSendBuffer, Client** clients, int sizeClients, int clientfd)
{
    return true;
}

/* Send the specified string to all connected clients but the one
 * having as socket descriptor 'excluded'. If you want to send something
 * to every client just set excluded to an impossible socket: -1. */
bool sendMsgToAllClientsBut(Client** clients, int sizeclients, int excluded, char *s) 
{
    bool ret=true;
    for (int j = 0; j <sizeclients; j++) 
    {
        if (clients[j] == NULL ||
            clients[j]->m_clientfd == excluded) continue;

        /* Important: we don't do ANY BUFFERING. We just use the kernel
         * socket buffers. If the content does not fit, we don't care.
         * This is needed in order to keep this program simple. */
       
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
			printf("write failed..\n");
			close(clients[j]->m_clientfd);
            continue;
        }
                
        ret = ret&&TcpWrite(clients[j]->m_clientfd,s);
    }
    return ret;
}

#endif