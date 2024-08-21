/*
*Author:wk
*Date:2024/8/22
*Description: the class for tcp read and write 
*/

#ifndef TCPLIB_H
#define TCPLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include<signal.h>
#include<assert.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/select.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

bool Readn(const int sockfd, char* buffer, const size_t n);
bool Writen(const int sockfd, char* buffer, const size_t n);
bool TcpRead(int sockfd, char* buffer, int* ibuflen, const int timeout=0);
bool TcpWrite(int sockfd, char* buffer, int* ibuflen=0);
void DeleteLChar(char *str,const char chr);
void DeleteRChar(char *str,const char chr);
void DeleteLRChar(char *str,const char chr);
void ToUpper(char *str);
void ToUpper(std::string& str);
bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,char *value,const int ilen=0);
bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,bool *value);
bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,int *value);
bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,unsigned int *value);
bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,long *value);
bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,unsigned long *value);
bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,double *value);

#endif