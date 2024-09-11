#include "DoSignUp.h"

DoSignUp::DoSignUp()
{
}

DoSignUp::DoSignUp(QObject *parent)
	: QObject(parent)
{
}

DoSignUp::~DoSignUp()
{}

RetCodeSignUp DoSignUp::SignUp(QString account, QString password, QString nickname)
{
	Identify identify(account.toUtf8(), password.toUtf8(), "");
	Data data(DataType::Text, nickname.length(), nickname.toUtf8());
	QByteArray xmlStr = m_xmlConstructor.ConstructSignUpRequestXml(identify, data);
	bool ret = Client::getInstance().m_tcpClient->Send(xmlStr, 0);

	Client::getInstance().m_tcpClient->TcpSocket()->waitForReadyRead(-1);	//等待直到有数据可读

	QByteArray xmlRecv = Client::getInstance().m_tcpClient->Recv();
	RetCodeSignUp retcode;
	m_xmlParser.ParseSignUpRetCodeXml(xmlRecv, &retcode);

	return retcode;
}
