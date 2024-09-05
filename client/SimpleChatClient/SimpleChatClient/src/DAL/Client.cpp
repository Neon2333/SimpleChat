#include "Client.h"


TcpClient* Client::m_tcpClient = nullptr;

Client::Client()
{
}

Client::~Client()
{
}

bool Client::setTcpClient(QString ip, unsigned int port)
{
	if (Client::m_tcpClient != nullptr)
	{
		//更换ip-port，重新连接
		if (Client::m_tcpClient->ResetIP(ip) && Client::m_tcpClient->ResetPort(port))
		{
			return true;
		}
		return false;
	}
	
	Client::m_tcpClient = new TcpClient(ip, port);
	return Client::m_tcpClient != nullptr;
}


