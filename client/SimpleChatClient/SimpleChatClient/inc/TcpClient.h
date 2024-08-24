#pragma once
#include<QObject>
#include<QHostAddress>
#include<QTcpSocket>
#include<QtEndian>
#include<QMessageBox> 
#include<QElapsedTimer>
#include<QCoreApplication>

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

public:
	TcpClient();
	TcpClient(QString ip, unsigned int port);
	~TcpClient();
	QString ServerIp();
	unsigned int Port();
	QTcpSocket* TcpSocket();
	char* Buffer();

	bool ConnectToServer();	//连接服务器
	bool ConnectToServer(QString ip, unsigned int port);	//连接服务器
	bool IsConnected();	//连接状态
	bool DisconnectFromServer();	//从服务器断开
	bool Send(QByteArray& buffer, int buflen);	//给服务器发字节，加上长度头
	QByteArray Recv();		//从服务器接收字符串，解析长度头

private slots:
	void onConnected();
	void onDisconnected();
	void onSendData(qint64 len);
	void onRecvData();

signals:
	void serverConnected();
	void serverDisconnected();
	void dataSended(qint64 len);
	void dataRecved(QByteArray msg);
};


