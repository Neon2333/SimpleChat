#include "DoSignUp.h"

DoSignUp::DoSignUp(QObject *parent)
	: QObject(parent)
{
}

DoSignUp::~DoSignUp()
{}

void DoSignUp::SignUp(QString account, QString password, QString nickname)
{
	Identify identify(account.toUtf8(), password.toUtf8(), "");
	Data data(DataType::Text, nickname.length(), nickname.toUtf8());
	QByteArray xmlStr = m_xmlConstructor.ConstructSignUpRequestXml(identify, data);
	bool ret = Client::getInstance().m_tcpClient->Send(xmlStr, 0);

	Client::getInstance().m_tcpClient->TcpSocket()->waitForReadyRead(-1);	//�ȴ�ֱ�������ݿɶ�

	QByteArray xmlRecv = Client::getInstance().m_tcpClient->Recv();
	RetCodeSignUp retcode;
	m_xmlParser.ParseSignUpRetCodeXml(xmlRecv, &retcode);
	switch (retcode)
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
}
