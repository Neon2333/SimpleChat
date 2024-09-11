#ifndef DOSIGNUP_H
#define DOSIGNUP_H
#include <QObject>
#include "Header.h"
#include "../inc/User.h"

class DoSignUp  : public QObject
{
	Q_OBJECT

public:
	DoSignUp();
	DoSignUp(QObject *parent);
	~DoSignUp();

	/// <summary>
	/// ע�����̺���
	/// ͬ��
	/// </summary>
	/// <param name="account"></param>
	/// <param name="password"></param>
	/// <param name="nickname"></param>
	/// <returns></returns>
	RetCodeSignUp SignUp(QString account, QString password, QString nickname);
private:
	XmlConstructor m_xmlConstructor;
	XmlParser m_xmlParser;
};

#endif // !DOSIGNUP_H