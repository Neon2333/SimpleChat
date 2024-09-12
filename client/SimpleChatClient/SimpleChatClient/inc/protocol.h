/*
Date:
Author:
Description:规定通信的xml的格式
*/

#ifndef PROTOCOL_H
#define	PROTOCOL_H

#include<vector>
#include<QString>

#define ACCOUNT_SIZE 20
#define PASSWORD_SIZE 20
#define TOKEN_SIZE 50

enum class MsgType	
{
	Heartbeat = 0,
	Request,
	Response,
	Ack
};

enum class BizCode	
{
	None=0,
	Signup=1,
	Login,
	Logout,
	Chat
};

enum class ForwCode	
{
	NoForward = 0,
	ForwardToAll,
	ForwardToOne,
	ForwardToGroup
};

enum class DataType	
{
	Text = 0,
	ImagePng=10,
	AudioMp3=20,
	VideoMp4=30
};

enum class RetCode
{
	Succeed = 0,
	Failed,
};

enum class RetCodeSignUp
{
	Succeed=10,
	Failed,
	AccountExisted
};

enum class RetCodeLogin
{
	Succeed=20,
	Failed,
	AlreadyLogin
};

enum class RetCodeLogout
{
	Succeed = 30,
	Failed,
};

enum class RetCodeChat
{
	Succeed = 40,
	Failed,
};

class Identify
{
public:
	QByteArray account;
	QByteArray password;
	QByteArray token;
public:
	Identify();
	Identify(QByteArray account, QByteArray password, QByteArray token);
	Identify(const Identify& another);
	Identify& operator=(const Identify& another);
	Identify(const Identify&& another);
	Identify& operator=(const Identify&& another);
	~Identify();

	void setAccount(QByteArray& account);
	void setPassword(QByteArray& password);
	void setToken(QByteArray& token);
};

class Forw
{
public:
	ForwCode forwcode;
	int receiveCount;
	std::vector<QString> receivers;
public:
	Forw();
	Forw(ForwCode forwcode, int count, std::vector<QString> receivers);
	~Forw();
};

class Data
{
public:
	DataType dataType;
	int dataSize;
	QByteArray databody;
public:
	Data();
	Data(DataType datatype, int size, QByteArray body);
	~Data();
};

#endif
