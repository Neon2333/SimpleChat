#ifndef DOSIGNUP_H
#define DOSIGNUP_H
#include <QObject>
#include "Header.h"
#include "../inc/User.h"

class DoSignUp  : public QObject
{
	Q_OBJECT

public:
	DoSignUp(QObject *parent);
	~DoSignUp();

	void SignUp(QString account, QString password, QString nickname);
private:
	XmlConstructor m_xmlConstructor;
	XmlParser m_xmlParser;
};

#endif // !DOSIGNUP_H