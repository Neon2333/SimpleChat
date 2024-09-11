#include"../inc/XmlParser.h"

XmlParser::XmlParser()
{
}

XmlParser::~XmlParser()
{
}

bool XmlParser::ParseMsgTypeXml(const QByteArray& xml, MsgType* msgtype)
{
	assert(msgtype != nullptr);

	const char* xmlTmp = xml.data();
	
	return GetXmlBuffer(xmlTmp, "msgtype", reinterpret_cast<int*>(msgtype));;
}

bool XmlParser::ParseBizCodeXml(const QByteArray& xml, BizCode* bizcode)
{
	assert(bizcode != nullptr);

	const char* xmlTmp = xml.data();

	return GetXmlBuffer(xmlTmp, "bizcode", reinterpret_cast<int*>(bizcode));;
}

bool XmlParser::ParseForwCodeXml(const QByteArray& xml, ForwCode* forwcode)
{
	assert(forwcode != nullptr);

	const char* xmlTmp = xml.data();

	return GetXmlBuffer(xmlTmp, "forwcode", reinterpret_cast<int*>(forwcode));;
}

bool XmlParser::ParseDataTypeXml(const QByteArray& xml, DataType* datatype)
{
	assert(datatype != nullptr);

	const char* xmlTmp = xml.data();

	return GetXmlBuffer(xmlTmp, "datatype", reinterpret_cast<int*>(datatype));;
}

bool XmlParser::ParseRetCodeXml(const QByteArray& xml, RetCode* retcode)
{
	assert(retcode != nullptr);

	const char* xmlTmp = xml.data();

	return GetXmlBuffer(xmlTmp, "retcode", reinterpret_cast<int*>(retcode));;
}

bool XmlParser::ParseSignUpRetCodeXml(const QByteArray& xml, RetCodeSignUp* retcode)
{
	assert(retcode != nullptr);

	const char* xmlTmp = xml.data();

	int bizcodeTmp;
	GetXmlBuffer(xmlTmp, "bizcode", &bizcodeTmp);
	assert(static_cast<BizCode>(bizcodeTmp) == BizCode::Signup);

	return GetXmlBuffer(xmlTmp, "retcode", reinterpret_cast<int*>(retcode));;
}

bool XmlParser::ParseLoginRetCodeXml(const QByteArray& xml, RetCodeLogin* retcode)
{
	assert(retcode != nullptr);
	const char* xmlTmp = xml.data();

	int bizcodeTmp;
	GetXmlBuffer(xmlTmp, "bizcode", &bizcodeTmp);
	assert(static_cast<BizCode>(bizcodeTmp) == BizCode::Login);

	return GetXmlBuffer(xmlTmp, "retcode", reinterpret_cast<int*>(retcode));;
}

bool XmlParser::ParseLogoutRetCodeXml(const QByteArray& xml, RetCodeLogout* retcode)
{
	assert(retcode != nullptr);
	const char* xmlTmp = xml.data();

	int bizcodeTmp;
	GetXmlBuffer(xmlTmp, "bizcode", &bizcodeTmp);
	assert(static_cast<BizCode>(bizcodeTmp) == BizCode::Logout);

	return GetXmlBuffer(xmlTmp, "retcode", reinterpret_cast<int*>(retcode));;
}

bool XmlParser::ParseChatRetCodeXml(const QByteArray& xml, RetCodeChat* retcode)
{
	assert(retcode != nullptr);
	const char* xmlTmp = xml.data();

	int bizcodeTmp;
	if (GetXmlBuffer(xmlTmp, "bizcode", &bizcodeTmp) == false)
		return false;
	assert(static_cast<BizCode>(bizcodeTmp) == BizCode::Chat);

	return GetXmlBuffer(xmlTmp, "retcode", reinterpret_cast<int*>(retcode));;
}

bool XmlParser::ParseIdentifyXml(const QByteArray& xml, Identify* identify)
{
	assert(identify != nullptr);

	const char* xmlTmp = xml.data();

	char accountTmp[ACCOUNT_SIZE];
	if (GetXmlBuffer(xmlTmp, "account", accountTmp, ACCOUNT_SIZE) == false)
		return false;
	identify->account = accountTmp;

	char passwordTmp[PASSWORD_SIZE];
	if (GetXmlBuffer(xmlTmp, "password", passwordTmp, PASSWORD_SIZE) == false)
		return false;
	identify->password = passwordTmp;

	char tokenTmp[TOKEN_SIZE];
	if (GetXmlBuffer(xmlTmp, "token", tokenTmp, TOKEN_SIZE) == false)
		return false;
	identify->token = tokenTmp;

	return true;
}

bool XmlParser::ParseForwXml(const QByteArray& xml, Forw* forw)
{
	assert(forw != nullptr);

	const char* xmlTmp = xml.data();

	int forwcode;
	if (GetXmlBuffer(xmlTmp, "forwcode", &forwcode) == false)
		return false;
	int receiveCount;
	if (GetXmlBuffer(xmlTmp, "rececount", &receiveCount) == false)
		return false;

	for (int i = 0; i < receiveCount; i++)
	{
		char accountReceiver[ACCOUNT_SIZE];
		QString fieldname = QString("receiver%1").arg(QString::number(i));
		if (GetXmlBuffer(xmlTmp, fieldname.toUtf8().data(), accountReceiver, ACCOUNT_SIZE) == false)
			return false;
		forw->receivers.emplace_back(QString(accountReceiver));
	}

	return true;
}

bool XmlParser::ParseDataXml(const QByteArray& xml, Data* data)
{
	assert(data != nullptr);
	const char* xmlTmp = xml.data();

	int datatype;
	if (GetXmlBuffer(xmlTmp, "datatype", &datatype) == false)
		return false;

	return false;
}


bool XmlParser::ParseHeartBeatXml(const QByteArray& xml, RetCode* retcode)
{
	assert(retcode != nullptr);
	const char* xmlTmp = xml.data();

	int msgtype;
	if (GetXmlBuffer(xmlTmp, "msgtype", &msgtype) == false)
		return false;
	assert(static_cast<MsgType>(msgtype) == MsgType::Heartbeat);

	return GetXmlBuffer(xmlTmp, "retcode", reinterpret_cast<int*>(retcode));
}

bool XmlParser::ParseAckXml(const QByteArray& xml, BizCode* bizcode, DataType* datatype, int* receivesize)
{
	assert(bizcode != nullptr);
	assert(datatype != nullptr);
	assert(receivesize != nullptr);

	const char* xmlTmp = xml.data();

	int msgtype;
	if (GetXmlBuffer(xmlTmp, "msgtype", &msgtype) == false)
		return false;
	assert(static_cast<MsgType>(msgtype) == MsgType::Ack);


	if (!GetXmlBuffer(xmlTmp, "bizcode", reinterpret_cast<int*>(bizcode)))
		return false;
	if (!GetXmlBuffer(xmlTmp, "datatype", reinterpret_cast<int*>(datatype)))
		return false;
	if (!GetXmlBuffer(xmlTmp, "receivesize", reinterpret_cast<int*>(receivesize)))
		return false;

	return true;
}

bool XmlParser::ParseResponseXml(const QByteArray xml, BizCode* bizcode, RetCode* retcode, Data* data)
{
	assert(bizcode != nullptr);
	assert(retcode != nullptr);
	assert(data != nullptr);

	const char* xmlTmp = xml.data();
	int msgtype;
	if (GetXmlBuffer(xmlTmp, "msgtype", &msgtype) == false)
		return false;
	assert(static_cast<MsgType>(msgtype) == MsgType::Response);

	if (!GetXmlBuffer(xmlTmp, "bizcode", reinterpret_cast<int*>(bizcode)))
		return false;
	if (!GetXmlBuffer(xmlTmp, "retcode", reinterpret_cast<int*>(retcode)))
		return false;

	if (data == nullptr)	return true;

	if (!GetXmlBuffer(xmlTmp, "datatype", reinterpret_cast<int*>(&(data->dataType))))
		return false;
	if (!GetXmlBuffer(xmlTmp, "datasize", reinterpret_cast<int*>(&(data->dataSize))))
		return false;
	if (!GetXmlBuffer(xmlTmp, "databody", reinterpret_cast<int*>(&(data->databody))))
		return false;

	return true;
}


