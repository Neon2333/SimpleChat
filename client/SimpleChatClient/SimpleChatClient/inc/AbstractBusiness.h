#pragma once

#include <QObject>
#include "Header.h"

class AbstractBusiness : public QObject
{
	Q_OBJECT

public:
	AbstractBusiness();
	AbstractBusiness(QObject *parent);
	virtual ~AbstractBusiness();

	virtual bool SendBusinessProcess(MsgType msgtype, BizCode bizcode, Identify& identify, Data& data, Forw& forw) = 0;
	virtual void RecvBusinessProcess() = 0;
};
