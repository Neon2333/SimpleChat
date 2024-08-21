/*
*Author:wk
*Date:2024/8/22
*Description: the class for dealing with business
*/

#include"Business.h"

//heartbeat
bool biz000(const char* strRecvBuffer,char* strSendBuffer)
{
    sprintf(strSendBuffer, "<message>heartbeat success</message>");
    return true;
}

//login
bool biz001(const char* strRecvBuffer,char* strSendBuffer)
{
    //resolve username and password from strRecvBuffer
    char username[51],password[51];
    memset(username,0,sizeof(username));
    memset(password,0,sizeof(password));
    
    GetXmlBuffer(strRecvBuffer,"username",username,50);
    GetXmlBuffer(strRecvBuffer,"password",password,50);
    
    //compare username and password in database
    if((strcmp(username, "wk")==0)&&(strcmp(password, "p@ssw0rd")==0))
        sprintf(strSendBuffer,"<retcode>0</retcode><message>login success</message>");  //replace bizcode to retcode
    else
        sprintf(strSendBuffer,"<retcode>-1</retcode><message>用户名或密码不正确</message>");
    
    return true;
}

//chat
bool biz002(const char* strRecvBuffer, char* strSendBuffer)
{
    //resolve forward type
    int iforwcode=-1;
    GetXmlBuffer(strRecvBuffer, "forwcode", &iforwcode);

    //resolve message 
    char message[501];
    memset(message,0,sizeof(message));
    GetXmlBuffer(strRecvBuffer,"message",message,500); //limit message size 500

    //construct xml
    int ilen=sprintf(strSendBuffer, "<retcode>0</retcode><forwcode>%d</forwcode><message>%s</message>", iforwcode, message);
    return ilen>0;
}