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
	bool Writen(const char* buffer, const qint64 size);	//���ճ�����ְ�
	bool Readn(char* buffer, const qint64 size);


	int m_remainTryCount = 0;	//ʣ�ೢ�����ӷ���������
	bool m_isConnected = false;	//�Ƿ������Ϸ�����
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

	void ConnectToServer();	//���ӷ�����
	void ConnectToServer(QString ip, unsigned int port);	//�Ͽ����������ӷ�����
	void TryConnectServer(const int tryCount, int* remainTryCount=nullptr);	//���Լ������ӷ�����
	bool ResetIP(QString ip);	//����ip
	bool ResetPort(unsigned int port);	//����port
	bool IsConnected();	//����״̬
	bool DisconnectFromServer();	//�ӷ������Ͽ�
	bool Send(QByteArray& buffer, const int buflen);	//�����������ֽڣ����ϳ���ͷ
	QByteArray Recv();		//�ӷ����������ַ�������������ͷ


signals:
	void serverConnected();
	void serverDisconnected();
	void dataSended(qint64 len);
	void dataRecved(QByteArray msg);
	void remainTryCountChanged(int remainTryCount);
};


