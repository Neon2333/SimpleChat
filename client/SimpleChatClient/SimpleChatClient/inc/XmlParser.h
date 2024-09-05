/*
	Description:自定义xml解析类
*/

#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QByteArray>
#include "../inc/protocol.h"
extern "C" {
#include "Md5.h"
}
#include "../inc/User.h"
#include "../inc/XmlHelper.h"


class XmlParser 
{
public:
	XmlParser();
	~XmlParser();

public:
	bool ParseMsgTypeXml(const QByteArray& xml, MsgType* msgtype);
	bool ParseBizCodeXml(const QByteArray& xml, BizCode* bizcode);
	bool ParseForwCodeXml(const QByteArray& xml, ForwCode* forwcode);
	bool ParseDataTypeXml(const QByteArray& xml, DataType* datatype);
	bool ParseRetCodeXml(const QByteArray& xml, RetCode* retcode);
	bool ParseSignUpRetCodeXml(const QByteArray& xml, RetCodeSignUp* retcode);
	bool ParseLoginRetCodeXml(const QByteArray& xml, RetCodeLogin* retcode);
	bool ParseLogoutRetCodeXml(const QByteArray& xml, RetCodeLogout* retcode);
	bool ParseChatRetCodeXml(const QByteArray& xml, RetCodeChat* retcode);

	bool ParseIdentifyXml(const QByteArray& xml, Identify* identify);
	bool ParseForwXml(const QByteArray& xml, Forw* forw);
	bool ParseDataXml(const QByteArray& xml, Data* data);

	bool ParseHeartBeatXml(const QByteArray& xml, RetCode* retcode);
	bool ParseAckXml(const QByteArray& xml, BizCode* bizcode, DataType* datatype, int* receivesize);
	bool ParseResponseXml(const QByteArray xml, BizCode* bizcode, RetCode* retcode, Data* data = nullptr);


};


#endif // !DATADECODER_H


