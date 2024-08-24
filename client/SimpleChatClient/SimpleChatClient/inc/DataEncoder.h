#ifndef DATAENCODER_H
#define DATAENCODER_H

#include<QByteArray>
#include<QString>
#include<Md5.h>
#include "../inc/protocol.hpp"
#include<vector>


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
	QByteArray ConstructRequestXml(BizCode bizcode, ForwCode forwcode, const QString& account, const QString& password, DataType datatype, const QByteArray& databody, const std::vector<QString>& receivers=std::vector<QString>());

	/// <summary>
	/// response
	/// </summary>
	QByteArray ConstructResponseXml(BizCode bizcode, const QString& account, RetCode retcode, DataType datatype, const QByteArray& databody);

	/// <summary>
	/// ack
	/// </summary>
	QByteArray ConstructAckXml(BizCode bizcode, const QString& account, DataType datatype, int receivedDatalen);

	/// <summary>
	/// heartbeat
	/// </summary>
	QByteArray ConstructHeartBeatXml();

	/// <summary>
	/// signup
	/// </summary>
	QByteArray ConstructSignUpRequestXml(const QString& account, const QString& password);

	/// <summary>
	/// login
	/// </summary>
	/// <param name="account"></param>
	/// <param name="password"></param>
	/// <returns></returns>
	QByteArray ContructLoginRequestXml(const QString& account, const QString& password);

	/// <summary>
	/// logout
	/// </summary>
	QByteArray ConstructLogoutRequestXml(const QString& account, const QString& password);

	/// <summary>
	/// chat
	/// </summary>
	QByteArray ConstructChatRequestXml(const QString& account, const QString& password, ForwCode forwcode, QByteArray databody, const std::vector<QString>& receivers);
};


#endif
