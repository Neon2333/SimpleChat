#ifndef DATAENCODER_H
#define DATAENCODER_H

#include<QByteArray>
#include<QString>
#include<vector>
#include<../inc/Md5.h>
#include "../inc/protocol.h"


class DataEncoder
{
private:	
	
public:
	DataEncoder();
	~DataEncoder();

	/// <summary>
	/// request
	/// </summary>
	/// <param name="bizcode">业务码</param>
	/// <param name="forwcode">转发码</param>
	/// <param name="account">用户账户</param>
	/// <param name="password">用户密码</param>
	/// <param name="datatype">数据类型</param>
	/// <param name="databody">数据体</param>
	/// <returns>构建的xml字符串</returns>
	QByteArray ConstructRequestXml(BizCode bizcode, const Identify& identify, const Data& data = Data(), const Forw& forw = Forw(), MsgType msgtype=MsgType::Request);

	/// <summary>
	/// response
	/// </summary>
	QByteArray ConstructResponseXml(BizCode bizcode, RetCode retcode, const Data data, MsgType msgtype);

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
	QByteArray ConstructSignUpRequestXml(Identify& identify);

	/// <summary>
	/// login
	/// </summary>
	/// <param name="account"></param>
	/// <param name="password"></param>
	/// <returns></returns>
	QByteArray ContructLoginRequestXml(Identify& identify);

	/// <summary>
	/// logout
	/// </summary>
	QByteArray ConstructLogoutRequestXml(Identify& identify);

	/// <summary>
	/// chat
	/// </summary>
	QByteArray ConstructChatRequestXml(Identify& identify, ForwCode forwcode, const Data& data, const Forw& forw);

};


#endif
