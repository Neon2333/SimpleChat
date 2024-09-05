#ifndef CLIENT_H
#define CLIENT_H
#include "../inc/TcpClient.h"

class Client
{
public:
	static TcpClient* m_tcpClient;

	Client();
	~Client();
	static bool setTcpClient(QString ip="172.20.10.3", unsigned int port=5000);

};


#endif // !CLIENT_H