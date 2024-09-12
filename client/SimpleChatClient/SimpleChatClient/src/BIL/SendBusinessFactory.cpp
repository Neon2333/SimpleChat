#include "SendBusinessFactory.h"

SendBusinessFactory::SendBusinessFactory(QObject *parent)
	: QObject(parent)
{}

SendBusinessFactory::~SendBusinessFactory()
{}

std::unique_ptr<AbstractBusiness> SendBusinessFactory::CreateBusiness(MsgType msgType, BizCode bizcode)
{
	if (MsgType::Heartbeat == msgType)
	{

	}
	else if (MsgType::Ack == msgType)
	{

	}
	else if (MsgType::Request == msgType || MsgType::Response == msgType)
	{
		switch (bizcode)
		{
		case BizCode::None:
			break;
		case BizCode::Signup:
			return std::unique_ptr<AbstractBusiness>(new SignUp);
			break;
		case BizCode::Login:
			break;
		case BizCode::Logout:
			break;
		case BizCode::Chat:
			break;
		default:
			return nullptr;
			break;
		}
	}


}
