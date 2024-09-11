#pragma once

#include <QObject>
#include "Header.h"

class BusinessFactory  : public QObject
{
	Q_OBJECT

public:
	BusinessFactory(QObject *parent);
	virtual ~BusinessFactory();

	virtual bool DoBusiness(BizCode bizcode) = 0;
};
