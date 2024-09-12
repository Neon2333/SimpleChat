#ifndef SENDBUSINESSFACTORY_H
#define SENDBUSINESSFACTORY_H
#include <QObject>
#include "Header.h"
#include "../inc/AbstractBusiness.h"
#include "../inc/SignUp.h"

class SendBusinessFactory  : public QObject
{
	Q_OBJECT

public:
	SendBusinessFactory(QObject *parent);
	~SendBusinessFactory();

	static std::unique_ptr<AbstractBusiness> CreateBusiness(MsgType msgType, BizCode bizcode=BizCode::None);
};

#endif