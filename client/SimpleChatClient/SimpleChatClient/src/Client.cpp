#include "Client.h"


//TcpClient* Client::m_tcpClient = nullptr;

Client::Client()
{
	m_tcpClient = nullptr;

	//从配置文件中读取ip-port
	m_clientConfig = ConfigOper::ReadConfig("./config/server.conf");
	if (m_clientConfig.at("host").empty() || m_clientConfig.at("port").empty())
	{
		m_clientConfig.at("host") = "127.0.0.1";
		m_clientConfig.at("port") = "5000";
	}
}

Client& Client::getInstance()
{
	static Client instance;
	return instance;
}

Client::~Client()
{
}

bool Client::initTcpClient()
{
	assert(m_tcpClient == nullptr);
	std::string ip = m_clientConfig.at("host");
	std::string port = m_clientConfig.at("port");
	assert(!ip.empty() && !port.empty());
	m_tcpClient = new TcpClient(QString::fromStdString(ip), static_cast<unsigned int>(std::stoi(port)));

	//服务器连上事件处理（连上服务器才保存ip-port）
	QObject::connect(m_tcpClient, &TcpClient::serverConnected, this, [=]() {
		m_clientConfig.at("host") = Client::m_tcpClient->ServerIp().toStdString();
		m_clientConfig.at("port") = std::to_string(Client::m_tcpClient->Port());
		ConfigOper::WriteConfig("./config/server.conf", m_clientConfig, ConfigWriteType::Cover);
		});

	//全局接收数据事件
	connect(m_tcpClient, &TcpClient::dataRecved, this, &Client::on_DataRecv);

	return false;
}

bool Client::resetTcpClient(QString ip, unsigned int port)
{
	assert(m_tcpClient != nullptr);

	//重置ip-port
	bool isIpReset = m_tcpClient->ResetIP(ip);
	bool isPortReset = m_tcpClient->ResetPort(port);
	if (isIpReset || isPortReset)
	{
		return true;
	}
	return false;

	return m_tcpClient != nullptr;
}

QByteArray Client::DataRecv()
{
	return m_dataRecv;
}

void Client::on_DataRecv(QByteArray datagram)
{
	m_dataRecv = datagram;
	//放到线程池处理接收到的数据
	XmlParser xmlParser;
	MsgType msgType;
	xmlParser.ParseMsgTypeXml(datagram, &msgType);


	switch (ret)
	{
	case RetCodeSignUp::Succeed:
		QMessageBox::information(nullptr, "info", "注册成功！");
		break;
	case RetCodeSignUp::Failed:
		QMessageBox::information(nullptr, "info", "注册失败！");
		break;
	case RetCodeSignUp::AccountExisted:
		QMessageBox::information(nullptr, "info", "账号已存在..");
		break;
	default:
		break;
	}

	switch (msgType)
	{
	case MsgType::Heartbeat:
		break;
	case MsgType::Request:
		break;
	case MsgType::Response:
		break;
	case MsgType::Ack:
		break;
	default:
		break;
	}
}


