#ifndef USER_H
#define	USER_H

#include <QByteArray>
#include "../inc/protocol.h"

class User
{
public:
	User();
	User(int uid, Identify& identify, QByteArray nickname, QByteArray createdTime);
	User(const User& another);
	User& operator=(const User& another);
	~User();

private:
	int m_uid;
	Identify m_identify;
	QByteArray m_nickname;
	QByteArray m_createdTime;

public:
	int Uid();
	bool SetUid(int uid);
	Identify GetIdentify();
	bool SetIdentify(Identify& identify);
	QByteArray Account();
	bool SetAccount(QByteArray account);
	QByteArray Password();
	bool SetPassword(QByteArray password);
	QByteArray Nickname();
	bool SetNickname(QByteArray nickname);
	QByteArray CreatedTime();
	bool setCreatedTime(QByteArray createdTime);
};

#endif // !USER_H




