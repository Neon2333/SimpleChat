#ifndef CLIENT_H
#define CLIENT_H
#include<QObject>
#include "Header.h"
#include <QThreadPool>


/// <summary>
/// ��ǰ�ͻ����࣬�������ӡ�ip��port�������������ļ���
/// </summary>
class Client : public QObject
{
	Q_OBJECT
private:
	Client();
	Client(const Client& another) = delete;
	Client& operator=(const Client& another) = delete;

	std::unordered_map<std::string, std::string> m_clientConfig;
	QByteArray m_dataRecv;
public:
	//static TcpClient* m_tcpClient;	
	TcpClient* m_tcpClient;

	static Client& getInstance();
	~Client();
	bool initTcpClient();
	bool resetTcpClient(QString ip, unsigned int port);
	QByteArray DataRecv();

private slots:
	void on_DataRecv(QByteArray datagram);


};


#endif // !CLIENT_H