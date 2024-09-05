#pragma once
#include<QObject>
#include<QHostAddress>
#include<QTcpSocket>
#include<QtEndian>
#include<QMessageBox> 
#include<QElapsedTimer>
#include<QCoreApplication>
#include <QThread>


#define BUFFER_SIZE 8192


class TcpClient	: public QObject
{
	Q_OBJECT
private:
	QHostAddress* m_serverIp;
	unsigned int m_port;
	QTcpSocket* m_tcpsocket;
	char* m_buffer;
	void initEvents();
	bool Writen(const char* buffer, const qint64 size);	//解决粘包、分包
	bool Readn(char* buffer, const qint64 size);


	int m_remainTryCount = 0;	//剩余尝试连接服务器次数
	bool m_isConnected = false;	//是否连接上服务器
public:
	int RemainTryCount();
	bool setRemainTryCount(int remainTryCount);

public:
	TcpClient();
	TcpClient(QString ip, unsigned int port);
	~TcpClient();
	QString ServerIp();
	unsigned int Port();
	QTcpSocket* TcpSocket();
	char* Buffer();

	void ConnectToServer();	//连接服务器
	void ConnectToServer(QString ip, unsigned int port);	//断开并重新连接服务器
	void TryConnectServer(const int tryCount, int* remainTryCount=nullptr);	//尝试几次连接服务器
	bool ResetIP(QString ip);	//重置ip
	bool ResetPort(unsigned int port);	//重置port
	bool IsConnected();	//连接状态
	bool DisconnectFromServer();	//从服务器断开
	bool Send(QByteArray& buffer, const int buflen);	//给服务器发字节，加上长度头
	QByteArray Recv();		//从服务器接收字符串，解析长度头


signals:
	void serverConnected();
	void serverDisconnected();
	void dataSended(qint64 len);
	void dataRecved(QByteArray msg);
	void remainTryCountChanged(int remainTryCount);
};


