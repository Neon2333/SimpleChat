#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class Client
{
public:
    int m_clientfd;
    char* m_ip;
    char* m_name;
public:
    Client()
    {
        m_ip=nullptr;
        m_name=nullptr;
    }
    Client(int fd,char* ip,char* name,int lenName):m_clientfd(fd)
    {
        if(m_ip==nullptr)
        {
            m_ip=(char*)malloc(16);
        }
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
        if(m_ip!=nullptr)
        {
            free(m_ip);
            m_ip=nullptr;
        }
        if(m_name!=nullptr)
        {
            free(m_name);
            m_name=nullptr;
        }
    }
};

#endif