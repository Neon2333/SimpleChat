#ifndef DOSIGNUP_H
#define DOSIGNUP_H
#include <QObject>
#include "Header.h"
#include "../inc/User.h"
#include "../inc/AbstractBusiness.h"

class SignUp : public QObject, public AbstractBusiness
{
	Q_OBJECT

public:
	SignUp();
	SignUp(QObject *parent);
	virtual ~SignUp();

	/// <summary>
	/// 注册流程函数
	/// 同步
	/// </summary>
	/// <param name="account"></param>
	/// <param name="password"></param>
	/// <param name="nickname"></param>
	/// <returns></returns>
	virtual bool SendBusinessProcess(MsgType msgtype, BizCode bizcode, Identify& identify, Data& data, Forw& forw) override;
	virtual void RecvBusinessProcess() override;

private:
	XmlConstructor m_xmlConstructor;
	XmlParser m_xmlParser;
};

#endif // !DOSIGNUP_H