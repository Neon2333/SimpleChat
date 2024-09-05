#include "../inc/User.h"

User::User()
{}

User::User(int uid, QByteArray account, QByteArray password, QByteArray nickname, QByteArray createdTime)
{
	m_uid = uid;
	m_account = account;
	m_password = password;
	m_nickname = nickname;
	m_createdTime = createdTime;
}

User::User(const User& another)
{
	m_uid = another.m_uid;
	m_account = another.m_account;
	m_password = another.m_password;
	m_nickname = another.m_nickname;
	m_createdTime = another.m_createdTime;
}

User& User::operator=(const User& another)
{
	if (this != &another)
	{
		m_uid = another.m_uid;
		m_account = another.m_account;
		m_password = another.m_password;
		m_nickname = another.m_nickname;
		m_createdTime = another.m_createdTime;
	}
	
	return *this;
}


User::~User()
{}

int User::Uid()
{
	return m_uid;
}

bool User::SetUid(int uid)
{
	m_uid = uid;
	return true;
}

QByteArray User::Account()
{
	return m_account;
}

bool User::SetAccount(QByteArray account)
{
	m_account = account;
	return true;
}

QByteArray User::Password()
{
	return m_password;
}

bool User::SetPassword(QByteArray password)
{
	m_password = password;
	return true;
}

QByteArray User::Nickname()
{
	return m_nickname;
}

bool User::SetNickname(QByteArray nickname)
{
	m_nickname = nickname;
	return true;
}

QByteArray User::CreatedTime()
{
	return m_createdTime;
}

bool User::setCreatedTime(QByteArray createdTime)
{
	m_createdTime = createdTime;
	return true;
}