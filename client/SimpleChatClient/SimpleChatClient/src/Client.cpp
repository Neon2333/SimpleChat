#include "Client.h"


//TcpClient* Client::m_tcpClient = nullptr;

Client::Client()
{
	m_tcpClient = nullptr;

	//�������ļ��ж�ȡip-port
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

	//�����������¼��������Ϸ������ű���ip-port��
	QObject::connect(m_tcpClient, &TcpClient::serverConnected, this, [=]() {
		m_clientConfig.at("host") = Client::m_tcpClient->ServerIp().toStdString();
		m_clientConfig.at("port") = std::to_string(Client::m_tcpClient->Port());
		ConfigOper::WriteConfig("./config/server.conf", m_clientConfig, ConfigWriteType::Cover);
		});

	//ȫ�ֽ��������¼�
	connect(m_tcpClient, &TcpClient::dataRecved, this, &Client::on_DataRecv);

	return false;
}

bool Client::resetTcpClient(QString ip, unsigned int port)
{
	assert(m_tcpClient != nullptr);

	//����ip-port
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
	//�ŵ��̳߳ش�����յ�������
	XmlParser xmlParser;
	MsgType msgType;
	xmlParser.ParseMsgTypeXml(datagram, &msgType);


	switch (ret)
	{
	case RetCodeSignUp::Succeed:
		QMessageBox::information(nullptr, "info", "ע��ɹ���");
		break;
	case RetCodeSignUp::Failed:
		QMessageBox::information(nullptr, "info", "ע��ʧ�ܣ�");
		break;
	case RetCodeSignUp::AccountExisted:
		QMessageBox::information(nullptr, "info", "�˺��Ѵ���..");
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


