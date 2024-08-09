#pragma once
#include<QObject>
#include<QHostAddress>
#include<QTcpSocket>
#include<QMessageBox> 

class TcpClient	: public QObject
{
	Q_OBJECT
private:
	QHostAddress* m_serverIp;
	unsigned int m_port;
	QTcpSocket* m_tcpsocket;
	void initEvents();

public:
	TcpClient();
	TcpClient(QString ip, unsigned int port);
	~TcpClient();
	QString ServerIp();
	unsigned int Port();
	bool ConnectToServer();	//连接服务器
	bool ConnectToServer(QString ip, unsigned int port);	//连接服务器
	bool IsConnected();	//连接状态
	bool DisconnectFromServer();	//从服务器断开
	bool Send(QString msg);		//给服务器发字符串
	QString Recv();		//从服务器接收字符串

private slots:
	void onConnected();
	void onDisconnected();
	void onSendData(qint64 len);
	void onRecvData();

signals:
	void serverConnected();
	void serverDisconnected();
	void dataSended(qint64 len);
	void dataRecved(QString msg);
};


