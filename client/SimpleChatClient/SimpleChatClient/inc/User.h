#ifndef USER_H
#define	USER_H

#include <QByteArray>
#include "../inc/protocol.h"

class User
{
public:
	User();
	User(int uid, QByteArray account, QByteArray password, QByteArray nickname, QByteArray token, QByteArray createdTime, QByteArray avatarPath);
	User(const User& another);
	User& operator=(const User& another);
	~User();

private:
	int m_uid;
	QByteArray m_account;
	QByteArray m_password;
	QByteArray m_nickname;
	QByteArray m_token;
	QByteArray m_createdTime;
	QByteArray m_avatarPath;

public:
	int Uid();
	bool SetUid(int uid);
	QByteArray Account();
	bool SetAccount(QByteArray account);
	QByteArray Password();
	bool SetPassword(QByteArray password);
	QByteArray Nickname();
	bool SetNickname(QByteArray nickname);
	QByteArray Token();
	bool SetToken(QByteArray token);
	QByteArray CreatedTime();
	bool SetCreatedTime(QByteArray createdTime);
	QByteArray AvatarPath();
	bool SetAvatarPath(QByteArray avatarPath);
};

#endif // !USER_H




