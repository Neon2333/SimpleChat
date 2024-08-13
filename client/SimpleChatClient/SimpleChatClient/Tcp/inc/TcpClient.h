#pragma once
#include<QObject>
#include<QHostAddress>
#include<QTcpSocket>
#include<QtEndian>
#include<QMessageBox> 
#include<QElapsedTimer>
#include<QCoreApplication>


class TcpClient	: public QObject
{
	Q_OBJECT
private:
	QHostAddress* m_serverIp;
	unsigned int m_port;
	QTcpSocket* m_tcpsocket;
	void initEvents();
	bool Writen(const char* buffer, qint64 size);	//���ճ�����ְ�

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
	bool Send(QByteArray buffer, int buflen);	//�����������ֽڣ����ϳ���ͷ
	QByteArray Recv();		//�ӷ����������ַ�������������ͷ

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


