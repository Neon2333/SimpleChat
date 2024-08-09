#include "TcpClient.h"






/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/select.h>
#include <netdb.h>


bool ConnectServer(int* sockfd, const char* ip, int port);

int main(int argc, char** argv)
{
    int serverfd = -1;
    if (ConnectServer(&serverfd, "127.0.0.1", atoi(argv[1])) == false)
    {
        printf("connect failed..\n");
        return -1;
    }
    printf("connected..\n");

    char buf[1024];
    int msgCount = 0;
    const int TESTCOUNT = 5;
    while (msgCount < TESTCOUNT)
        //while(true)
    {
        memset(buf, 0, sizeof(buf));
        //printf("enter input:\n");
        //scanf("%s",buf);

        sprintf(buf, "this is msg %d", msgCount);
        if (send(serverfd, buf, strlen(buf), 0) == false)
        {
            printf("send error..\n");
            return -1;
        }
        printf("send:%s\n", buf);

        memset(buf, 0, sizeof(buf));
        if (recv(serverfd, buf, sizeof(buf), 0) == false)
        {
            printf("recv error..\n");
            return -1;
        }
        printf("recv:%s\n", buf);
        sleep(1);
        msgCount++;
    }

    printf("msgCount=%d\n", msgCount);

    return 0;
}

bool ConnectServer(int* sockfd, const char* ip, int port)
{
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;

    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    *sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (*sockfd == -1)
    {
        return false;
    }

    if (connect(*sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        close(*sockfd);
        *sockfd = -1;
        return false;
    }

    return true;
}

*/

void TcpClient::initEvents()
{
    connect(m_tcpsocket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(m_tcpsocket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(m_tcpsocket, &QTcpSocket::bytesWritten, this, &TcpClient::onSendData);
    connect(m_tcpsocket, &QTcpSocket::disconnected, this, &TcpClient::onRecvData);
}

TcpClient::TcpClient()
{
    m_serverIp = new QHostAddress();
    m_tcpsocket = new QTcpSocket(nullptr);
    m_port = -1;
    initEvents();
}

TcpClient::TcpClient(QString ip, unsigned int port):m_port(port)
{
    initEvents();
    m_serverIp = new QHostAddress();
    if (m_serverIp->setAddress(ip))
    {
        QMessageBox::information(nullptr,"error","server ip address error..");
    }
}

TcpClient::~TcpClient()
{
    delete m_serverIp;
    delete m_tcpsocket;
}

QString TcpClient::ServerIp()
{
    if(!m_serverIp->isNull())
        return m_serverIp->toString();
    return nullptr;
}

unsigned int TcpClient::Port()
{
    return m_port;
}

bool TcpClient::ConnectToServer()
{
    if (m_serverIp->isNull())
        return false;
    m_tcpsocket->connectToHost(*m_serverIp, m_port);
    m_tcpsocket->waitForConnected();
    int ret = m_tcpsocket->state();
    return m_tcpsocket->state() == QAbstractSocket::ConnectedState;
}

bool TcpClient::ConnectToServer(QString ip, unsigned int port)
{
    if (IsConnected())
    {
        DisconnectFromServer();
    }
    
    if (!m_serverIp->setAddress(ip))
    {
        QMessageBox::information(nullptr, "info", "server ip or port error..");
    }
    m_port = port;
    
    return ConnectToServer();
}

bool TcpClient::IsConnected()
{
    return m_tcpsocket->state() == QAbstractSocket::ConnectedState;
}

bool TcpClient::DisconnectFromServer()
{
    m_tcpsocket->disconnectFromHost();
    m_tcpsocket->waitForDisconnected(3000);
    return m_tcpsocket->state() == QAbstractSocket::UnconnectedState;
}

bool TcpClient::Send(QString msg)
{
    QByteArray msgtmp = msg.toUtf8();
    int ilen = m_tcpsocket->write(msgtmp);
    return ilen == msgtmp.size();
    m_tcpsocket->flush();
}

QString TcpClient::Recv()
{
    int isize = 0;
    while ((isize = m_tcpsocket->bytesAvailable()) > 0)
    {
        QByteArray datagram;
        datagram.resize(isize);
        m_tcpsocket->read(datagram.data(), datagram.size());
        QString msgtmp = datagram.data();
        return msgtmp;
    }

    return QString();
}

void TcpClient::onConnected()
{
    emit serverConnected();
}

void TcpClient::onDisconnected()
{
    m_tcpsocket->deleteLater();
    emit serverDisconnected();
}

void TcpClient::onSendData(qint64 len)
{
    emit dataSended(len);
}

void TcpClient::onRecvData()
{
    QString msgRecv = Recv();
    emit dataRecved(msgRecv);
}