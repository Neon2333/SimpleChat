/*
*Author:wk
*Date:2024/8/22
*Description: main 
*/

#include "Tcplib.h"
#include "TcpServer.h"
#include "CLogFile.h"
#include "Client.hpp"
#include "Business.h"
#include "Forward.hpp"

#define SIZECLIENTS 1000
CLogFile g_logfile;
TcpServer g_tcpServer;
Client* g_clients[SIZECLIENTS];  //pointer array
int g_clientsCount;
int g_epollfd;
struct epoll_event g_ev;

bool BusinessProcess(const char* strRecvBuffer,char* strSendBuffer, int* bizcode);
bool ForwardProcess(char* strSendBuffer, Client** clients, int sizeClients, int clientfd, int* forwcode);
Client* addClient(int clientfd,char* ip);
void delClient(Client *client);
bool addfd(int epollfd, int fd, struct epoll_event* ev);
void MainExit(int sig);

int main(int argc,char** argv)
{
    if(argc!=3)	
    {
        //格式：端口 日志文件路径
        printf("Using: ./simplechat_server port logfile\nExample:./simplechat_server 5000 /tmp/simplechat.log\n\n");
        return -1;
    }
   
    //屏蔽所有信号
    for(int i=0;i<70;i++)
    {
        signal(i, SIG_IGN);
    }
    //设定信号2和15处理函数主进程退出
    signal(SIGINT,MainExit);	
    signal(SIGTERM,MainExit);
    
    g_logfile.m_bBackup=false; //多进程服务程序关闭日志切换
    if(g_logfile.Open(argv[2], "a+") == false)	//a+添加，不存在则创建
    {
        printf("logfile open failed..(%s)\n", argv[2]);
    }

    if(g_tcpServer.InitServer(atoi(argv[1]))==false)
    {
        g_logfile.Write("server init failed..\n");
        MainExit(-1);
    }

    memset(g_clients,0,SIZECLIENTS*sizeof(Client*));
    g_clientsCount=0;
    int epollfd=epoll_create(1);
    if(epollfd<0)   g_logfile.Write("epoll_create failed..\n");

    struct epoll_event ev;
    addfd(epollfd, g_tcpServer.m_listenfd, &ev);

    while(true)
    {
        struct epoll_event events[SIZECLIENTS+1];	//epoll_wait返回时保存发生的事件
        int infds=epoll_wait(epollfd,events,SIZECLIENTS+1,-1);
        if(infds<0) 
        {
            g_logfile.Write("epoll_wait failed..\n");
            break;
        }
        if(infds==0)
        {
            g_logfile.Write("epoll_wait timeout..\n");
            break;
        }
        
        //发生的事件再events中从index=0依次保存
        for(int i=0;i<infds;i++) 
        {
            //listenfd上有数据可读事件发生
            if((events[i].data.fd==g_tcpServer.m_listenfd) && (events[i].events&EPOLLIN))
            {
                if(false==g_tcpServer.Accept())
                {
                    g_logfile.Write("accept failed..\n");
                    continue;
                }

                //连接上的客户端添加进监视
                memset(&ev,0,sizeof(struct epoll_event));	//清空ev
                ev.data.fd=g_tcpServer.m_clientfd;
                ev.events=EPOLLIN;
                epoll_ctl(epollfd,EPOLL_CTL_ADD,g_tcpServer.m_clientfd,&ev);
                Client* client = addClient(g_tcpServer.m_clientfd,g_tcpServer.GetIP());
                /* Send a welcome message. */
                /*
                char welcome_msg[1024]=
                    "Welcome to Simple Chat! "
                    "Use /nick <nick> to set your nick.\n";
                g_tcpServer.Write(welcome_msg);
                //g_logfile.Write("%ld client(%s) connectd..\n",time(0),g_tcpServer.GetIP());
                */
                g_logfile.Write("%ld client(%d) connectd..\n",time(0),g_tcpServer.m_clientfd);
                continue;
            }
            else if(events[i].events&EPOLLIN)	//有数据可读事件
            {
                char recvBuf[1024];
                char sendBuf[1024];
                memset(recvBuf,0,sizeof(recvBuf));
                memset(sendBuf,0,sizeof(sendBuf));
                int isize=-1;
                if(false==TcpRead(events[i].data.fd, recvBuf, &isize))
                {
                   //把客户端fd从监视中删除
                    memset(&ev,0,sizeof(struct epoll_event));
                    ev.data.fd=events[i].data.fd;
                    ev.events=EPOLLIN;
                    epoll_ctl(epollfd,EPOLL_CTL_DEL,events[i].data.fd,&ev);
                    close(events[i].data.fd);
                    g_logfile.Write("%ld client(%d) disconneted..\n",time(0),events[i].data.fd);
                    delClient(g_clients[events[i].data.fd]);
                    continue;
                }
/*
                if(isize<=0)
                {
                    //把客户端fd从监视中删除
                    memset(&ev,0,sizeof(struct epoll_event));
                    ev.data.fd=events[i].data.fd;
                    ev.events=EPOLLIN;
                    epoll_ctl(epollfd,EPOLL_CTL_DEL,events[i].data.fd,&ev);
                    close(events[i].data.fd);
                    g_logfile.Write("%ld client(%d) disconneted..\n",time(0),events[i].data.fd);
                    delClient(g_clients[events[i].data.fd]);
                    continue;
                }
*/ 
                //g_logfile.Write("client(%d)recv msg:%s,size=%d\n",events[i].data.fd,buf,isize);
                g_logfile.Write("recv:%s",recvBuf);
                int ibizcode=-1;
                if(false==BusinessProcess(recvBuf, sendBuf, &ibizcode))
                {
                    g_logfile.Write("biz failed...(client %d),bizcode=%d\n",events[i].data.fd,ibizcode);
                }

                int iforwcode=-1;
                if(false==ForwardProcess(sendBuf, g_clients, SIZECLIENTS, events[i].data.fd, &iforwcode))
                {
                    g_logfile.Write("forward failed...(client %d),forwcode=%d\n",events[i].data.fd,iforwcode);
                }
               
            }
       }
    }
    return 0;
}


//add client to g_clients
Client* addClient(int clientfd,char* ip) 
{
    char nametmp[64];
    int namelen = snprintf(nametmp,64,"user:%d",clientfd);
    Client* client = new Client(clientfd,ip,nametmp,namelen);
    
    assert(g_clients[client->m_clientfd] == nullptr); // This should be available.
    //g_clients[client->m_clientfd]->m_clientfd =clientfd;
    g_clients[clientfd]=client;
    g_clientsCount++; 
    return client;
}

//remove client from g_clients
void delClient(Client *client) 
{
    g_clients[client->m_clientfd]=nullptr;
    g_clientsCount--; 
    
    if(client!=nullptr)
    {
        delete client;
        client==nullptr;
    }
}

//add fd to epoll
bool addfd(int epollfd, int fd, struct epoll_event* ev)
{
    memset(ev,0,sizeof(struct epoll_event));
    ev->data.fd=fd;
    ev->events=EPOLLIN;
    //setnoblocking(fd);
    return 0==epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,ev);	//添加到epollfd
}

//MainProcess clean function
void MainExit(int sig)
{
    if(sig>0)	
    {
        signal(sig,SIG_IGN);
        signal(SIGINT,SIG_IGN);
        signal(SIGTERM,SIG_IGN);
        
        kill(0,15);	
        printf("simplechat exited..(main process:%d)\n",getpid());
        
        g_tcpServer.CloseListen();
        for(int i=0;i<SIZECLIENTS;i++)
        {
            delete g_clients[i];
        }
        exit(0);
    }
}

//业务处理函数
//strRecvBuffer-接收报文
//strSendBuffer-发送报文
bool BusinessProcess(const char* strRecvBuffer,char* strSendBuffer, int* bizcode)
{
    GetXmlBuffer(strRecvBuffer,"bizcode", bizcode);
    
    switch(*bizcode)
    {
        case 0: 
            {return biz000(strRecvBuffer,strSendBuffer);    break;}
        case 1:
            {return biz001(strRecvBuffer,strSendBuffer);    break;}
        case 2:
            {return biz002(strRecvBuffer,strSendBuffer);    break;}
        default:
            g_logfile.Write("非法报文：%s\n",strSendBuffer);	
            return false;
    }
}

//forward message through forwcode
bool ForwardProcess(char* strSendBuffer, Client** clients, int sizeClients, int clientfd, int* forwcode)
{
    GetXmlBuffer(strSendBuffer,"forwcode", forwcode);
    
    switch(*forwcode)
    {
        case 0: 
            g_logfile.Write("send: %s\n", strSendBuffer);  
            return forw000(strSendBuffer, clients, sizeClients, clientfd);    
            break;
        case 1:
            g_logfile.Write("send: %s\n", strSendBuffer);  
            return forw001(strSendBuffer, clients, sizeClients, clientfd);    
            break;
        case 2:
            g_logfile.Write("send: %s\n", strSendBuffer);  
            return forw002(strSendBuffer, clients, sizeClients, clientfd);    
            break;
        default:
            //g_logfile.Write("not forward..\n：%s\n",strSendBuffer);	
            return false;
    }
}