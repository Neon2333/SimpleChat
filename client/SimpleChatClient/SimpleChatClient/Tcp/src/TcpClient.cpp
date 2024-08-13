#include "../inc/TcpClient.h"

void TcpClient::initEvents()
{
    connect(m_tcpsocket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(m_tcpsocket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(m_tcpsocket, &QTcpSocket::bytesWritten, this, &TcpClient::onSendData);
    connect(m_tcpsocket, &QTcpSocket::readyRead, this, &TcpClient::onRecvData);
}

bool TcpClient::Writen(const char* buffer, qint64 size)
{
    if (m_tcpsocket == nullptr)    return false;

    int ileft, isend, idx;
    ileft = size;
    isend = 0;
    idx = 0;
    while (ileft > 0)
    {
        if (isend = m_tcpsocket->write(buffer, ileft) <= 0)
        {
            QMessageBox::information(nullptr, "error", "NULL");
            return false;
        }
        ileft -= isend;
        idx += isend;
    }
    bool res = m_tcpsocket->flush();

    return res;
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


bool TcpClient::Send(QByteArray buffer, int buflen)
{
    int ilen = 0;
    if (buflen == 0)
        ilen = strlen(buffer);
    else
        ilen = buflen;

    char lenn[4] = { 0 };
    qToBigEndian<qint32>(ilen, lenn); //ilen转网络序
    buffer.prepend((const char*)lenn, 4);  //把长度ilenn添加在buffer前面

    //if (Writen(buffer, static_cast<qint64>(ilen)+4) == false)    return false;
    int isend = m_tcpsocket->write(buffer);
    if(4+ilen!=isend)    return false;
    //return m_tcpsocket->waitForBytesWritten();
    return m_tcpsocket->flush();
}

QByteArray TcpClient::Recv()
{
    int isize = 0;
    if ((isize=m_tcpsocket->bytesAvailable()) == 0)
    {
        return nullptr;
    }


    //非阻塞延时
    QElapsedTimer t;
    t.start();
    while (t.elapsed() < 500) QCoreApplication::processEvents();

    //TODO:read完数据还会被触发1次？？？
    QByteArray data = m_tcpsocket->readAll();

    int imsgLenn = 0;
    memcpy(&imsgLenn, data.data(), 4);
    int imsgLen = qFromBigEndian(imsgLenn);
    
    char* buffer = (char*)malloc(imsgLen);
    assert(buffer != nullptr);
    memset(buffer, 0, imsgLen);
    memcpy(buffer, data.data() + 4, imsgLen);
    QByteArray msg(buffer, imsgLen);
    free(buffer);
    return msg;



    //int imsgLenn = 0;    
    //m_tcpsocket->read((char*)&imsgLenn, 4);
    //int imsgLen = qFromBigEndian(imsgLenn); //数据包长度

    //QByteArray datagram;
    //datagram.resize(imsgLen);
    //while(m_tcpsocket->bytesAvailable() > 0)
    //{
    //    m_tcpsocket->read(datagram.data(), datagram.size());
    //}

    //return datagram;
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
    QByteArray msgRecv = Recv();
    if (msgRecv == nullptr)
        return;
    emit dataRecved(msgRecv);
}