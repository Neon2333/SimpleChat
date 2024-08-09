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
	bool ConnectToServer();	//���ӷ�����
	bool ConnectToServer(QString ip, unsigned int port);	//���ӷ�����
	bool IsConnected();	//����״̬
	bool DisconnectFromServer();	//�ӷ������Ͽ�
	bool Send(QString msg);		//�����������ַ���
	QString Recv();		//�ӷ����������ַ���

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


