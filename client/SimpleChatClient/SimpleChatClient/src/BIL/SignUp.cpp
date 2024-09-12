#include "SignUp.h"

SignUp::SignUp()
{
}

SignUp::SignUp(QObject *parent)
	: QObject(parent)
{
}

SignUp::~SignUp()
{}

bool SignUp::SendBusinessProcess(MsgType msgtype, BizCode bizcode, Identify& identify, Data& data, Forw& forw)
{
	//发送注册请求
	Data& nickname = data;
	QByteArray xmlStr = m_xmlConstructor.ConstructSignUpRequestXml(identify, nickname);
	bool ret = Client::getInstance().m_tcpClient->Send(xmlStr, 0);

	return ret;
}

void SignUp::RecvBusinessProcess()
{
	//接收注册响应
}
