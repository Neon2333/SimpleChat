#include "../inc/TcpClient.h"

void TcpClient::initEvents()
{
    connect(m_tcpsocket, &QTcpSocket::connected, this, [=]() {
        m_isConnected = true;
        emit serverConnected();
        });

    connect(m_tcpsocket, &QTcpSocket::disconnected, this, [=]() {
        m_isConnected = false;
        emit serverDisconnected();
        });

    connect(m_tcpsocket, &QTcpSocket::bytesWritten, this, [=](qint64 len) {
        emit dataSended(len);
        });

    connect(m_tcpsocket, &QTcpSocket::readyRead, this, [=]() {
        emit dataRecved(Recv());
        });
}

bool TcpClient::Writen(const char* buffer, qint64 size)
{
    if (m_tcpsocket == nullptr || buffer==nullptr)    return false;

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

bool TcpClient::Readn(char* buffer, const qint64 size)
{
    if (m_tcpsocket == nullptr || buffer == nullptr) return false;

    qint64 nleft, nread, idx;
    nleft = size;
    nread = 0;
    idx = 0;
    while (nleft > 0)
    {
        if ((nread = m_tcpsocket->read(buffer + idx, nleft)) <= 0)
        {
            return false;
        }
        nleft -= nread;
        idx += nread;
    }
    return true;
}

int TcpClient::RemainTryCount()
{
    return m_remainTryCount;
}

bool TcpClient::setRemainTryCount(int remainTryCount)
{
    if (m_remainTryCount == remainTryCount)  return true;
    m_remainTryCount = remainTryCount;
    emit remainTryCountChanged(m_remainTryCount);
    return true;
}

TcpClient::TcpClient()
{
    if(m_serverIp == nullptr)   m_serverIp = new QHostAddress();
    if(m_tcpsocket == nullptr)  m_tcpsocket = new QTcpSocket(nullptr);

    m_buffer = new char[BUFFER_SIZE];
    memset(m_buffer, 0, BUFFER_SIZE);
    initEvents();
}

TcpClient::TcpClient(QString ip, unsigned int port)
{
    if (m_serverIp == nullptr)   m_serverIp = new QHostAddress();
    if (m_tcpsocket == nullptr)  m_tcpsocket = new QTcpSocket(nullptr);

    m_buffer = new char[BUFFER_SIZE];
    memset(m_buffer, 0, BUFFER_SIZE);
    assert(true == setServerIp(ip));
    assert(true == setPort(port));
    initEvents();
}

TcpClient::~TcpClient()
{
    delete m_serverIp;
    m_tcpsocket->deleteLater();
}

bool TcpClient::setServerIp(QString ip)
{
    assert(!ip.isEmpty());

    if (m_serverIp != nullptr && ip == m_serverIp->toString())    return false;

    if (m_serverIp->setAddress(ip))
    {
        m_isServerIpChanged = true;
        if (!m_isServerPortChanged)     //防止ip、port信号
        {
            emit serverIpChanged();
        }
        return true;
    }
    return false;
}

bool TcpClient::setPort(unsigned int port)
{
    if (m_port != 0 && port == m_port)  return false;
    
    m_port = port;
    m_isServerPortChanged = true;
    if(!m_isServerIpChanged)    emit serverPortChanged();
    return true;
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

char* TcpClient::Buffer()
{
    return m_buffer;
}

QTcpSocket* TcpClient::TcpSocket()
{
    return m_tcpsocket;
}

void TcpClient::ConnectToServer()
{
    if (IsConnected())
    {
        DisconnectFromServer();
    }

    if (m_serverIp->isNull())
        return;
    if (m_tcpsocket->state() == QAbstractSocket::ConnectedState || m_tcpsocket->state() == QAbstractSocket::ConnectingState)
        return;
    //异步连接，通过信号获知已连接
    m_tcpsocket->connectToHost(*m_serverIp, m_port);
    //QThread* th = new QThread();
    //m_tcpsocket->moveToThread(th);
    //th->start();
    //m_tcpsocket->waitForConnected(5000);    //等待5s
    //th->exit();
    //th->wait();
    //th->deleteLater();
    bool ret = (m_tcpsocket->state() == QAbstractSocket::ConnectedState);
    //重置标志
    m_isServerIpChanged = false;
    m_isServerPortChanged = false;
}

void TcpClient::ConnectToServer(QString ip, unsigned int port)
{
    if (IsConnected())
    {
        DisconnectFromServer();
    }
    
    if (!setServerIp(ip))
    {
        QMessageBox::information(nullptr, "info", "server ip or port error..");
    }
    m_port = port;
    
    ConnectToServer();
}

void TcpClient::TryConnectServer(const int tryCount, int* remainTryCount)
{
    m_remainTryCount = tryCount;
    int remianTmp = tryCount;
    //循环连接服务器
    while (m_remainTryCount > 0 && !IsConnected())
    {
        ConnectToServer();
        setRemainTryCount(--remianTmp);
        if (remainTryCount != nullptr)  *remainTryCount = m_remainTryCount;
    }
}

bool TcpClient::ResetIP(QString ip)
{
    if (!setServerIp(ip))   return false;

    if (IsConnected())
        return DisconnectFromServer();
    else
        return false;
}

bool TcpClient::ResetPort(unsigned int port)
{
    if (!setPort(port))  return false;

    if (IsConnected())
        return DisconnectFromServer();
    else
        return false;
}

bool TcpClient::IsConnected()
{
    //return m_tcpsocket->state() == QAbstractSocket::ConnectedState;
    return m_isConnected;
}

bool TcpClient::DisconnectFromServer()
{
    m_tcpsocket->disconnectFromHost();
    //m_tcpsocket->waitForDisconnected(3000);
    m_tcpsocket->close();
    return m_tcpsocket->state() == QAbstractSocket::UnconnectedState;
}


bool TcpClient::Send(QByteArray& buffer, const int buflen)
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
    int isize = 0;
    while (m_tcpsocket->bytesToWrite() > 0)
    {
        isize += m_tcpsocket->write(buffer);
        if (4 + ilen == isize)
        {
            break;
        }
    }
    return m_tcpsocket->waitForBytesWritten();
    //return m_tcpsocket->flush();
}

QByteArray TcpClient::Recv()
{
    int isize = 0;
    if ((isize=m_tcpsocket->bytesAvailable()) == 0)
    {
        return nullptr;
    }

   /* QByteArray package = m_tcpsocket->readAll();

    int imsgLenn = 0;
    memcpy(&imsgLenn, package.data(), 4);
    int imsgLen = qFromBigEndian(imsgLenn);

    memset(m_buffer, 0, BUFFER_SIZE);
    memcpy(m_buffer, package.data() + 4, imsgLen);
    QByteArray data(m_buffer, imsgLen);
    return data;*/

    int imsgLenn = 0;    
    m_tcpsocket->read((char*)&imsgLenn, 4);
    int imsgLen = qFromBigEndian(imsgLenn); //数据包长度

    if ((isize = m_tcpsocket->bytesAvailable()) >= imsgLen)
    {
        QByteArray datagram;
        datagram.resize(imsgLen);
        m_tcpsocket->read(datagram.data(), datagram.size());
        return datagram;
    }
    else
    {
        return nullptr;
    }
}

