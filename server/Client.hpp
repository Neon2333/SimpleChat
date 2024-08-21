/*
*Author:wk
*Date:2024/8/22
*Description: the class for describing clients
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class Client
{
public:
    int m_clientfd;
    char m_ip[16];
    char* m_name;
public:
    Client()
    {
        m_name=nullptr;
    }
    Client(int fd,char* ip,char* name,int lenName):m_clientfd(fd)
    {
        memset(m_ip,0,16);
        memcpy(m_ip,ip,16);

        if(m_name==nullptr)
        {
            m_name=(char*)malloc(lenName+1);
        }
        memset(m_name,0,lenName+1);
        memcpy(m_name,name,lenName);//    lenName
    }
    ~Client()
    {
        if(m_name!=nullptr)
        {
            free(m_name);
            m_name=nullptr;
        }
    }
};

#endif