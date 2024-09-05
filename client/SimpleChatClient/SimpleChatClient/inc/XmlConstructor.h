/*
		TODO:暂时先用拼字符串生成xml
		Description:自定义xml解析类
*/



#ifndef XMLCONSTRUCTOR_H
#define XMLCONSTRUCTOR_H

#include<QByteArray>
#include<QString>
#include<vector>
#include "../inc/protocol.h"
#include "../inc/User.h"
#include "../inc/XmlHelper.h"
#include "../inc/EncryptHelper.h"

/// <summary>
/// 封装
/// </summary>
class XmlConstructor
{
private:	
	
public:
	XmlConstructor();
	~XmlConstructor();

public:

	/// <summary>
	/// request
	/// </summary>
	/// <param name="bizcode"></param>
	/// <param name="identify"></param>
	/// <param name="data"></param>
	/// <param name="forw"></param>
	/// <param name="msgtype"></param>
	/// <returns></returns>
	QByteArray ConstructRequestXml(BizCode bizcode, const Identify& identify, const Data& data = Data(), const Forw& forw = Forw(), MsgType msgtype=MsgType::Request);

	/// <summary>
	/// response
	/// </summary>
	QByteArray ConstructResponseXml(BizCode bizcode, RetCode retcode, const Data& data, MsgType msgtype);

	/// <summary>
	/// ack
	/// </summary>
	QByteArray ConstructAckXml(BizCode bizcode, DataType datatype, int receivedDatalen, MsgType msgtype=MsgType::Ack);

	/// <summary>
	/// heartbeat
	/// </summary>
	QByteArray ConstructHeartBeatXml();

	/// <summary>
	/// signup
	/// </summary>
	QByteArray ConstructSignUpRequestXml(Identify& identify, Data& nickname);

	/// <summary>
	/// login
	/// </summary>
	/// <param name="account"></param>
	/// <param name="password"></param>
	/// <returns></returns>
	QByteArray ConstructLoginRequestXml(Identify& identify);

	/// <summary>
	/// logout
	/// </summary>
	QByteArray ConstructLogoutRequestXml(Identify& identify);

	/// <summary>
	/// chat
	/// </summary>
	QByteArray ConstructChatRequestXml(Identify& identify, const Data& data, const Forw& forw);


	QByteArray ConstructSignUpRequestXml(User& user);

	QByteArray ConstructLoginRequestXml(User& user);

	QByteArray ConstructLogoutRequestXml(User& user);

	QByteArray ConstructChatRequestXml(User& user, QByteArray chatMsg, const Forw& forw);

};


#endif
