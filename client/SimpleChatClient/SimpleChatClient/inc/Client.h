#ifndef CLIENT_H
#define CLIENT_H
#include<QObject>
#include "../inc/TcpClient.h"
#include "../inc/configOper.h"


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
public:
	//static TcpClient* m_tcpClient;	
	TcpClient* m_tcpClient;

	static Client& getInstance();
	~Client();
	bool initTcpClient();
	bool resetTcpClient(QString ip, unsigned int port);

};


#endif // !CLIENT_H