/*
*Author:wk
*Date:2024/8/22
*Description: the class for dealing with business
*/

#ifndef BUSINESS_H
#define BUSINESS_H
#include "Tcplib.h"

bool biz000(const char* strRecvBuffer,char* strSendBuffer);
bool biz001(const char* strRecvBuffer,char* strSendBuffer);
bool biz002(const char* strRecvBuf, char* strSendbuf);

#endif