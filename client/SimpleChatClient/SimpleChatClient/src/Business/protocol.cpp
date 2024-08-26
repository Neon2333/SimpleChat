#include "../../inc/protocol.h"

#define ACCOUNT_SIZE 20
#define PASSWORD_SIZE 20
#define TOKEN_SIZE 50


Identify::Identify():account(""), password(""), token("")
{}

Identify::Identify(QString account, QString password, QString token) :account(account), password(password), token(token)
{}

Identify::Identify(Identify&& another) 
{
	this->account = std::move(another.account);
	this->password = std::move(another.password);
	this->token = std::move(another.token);
}

Identify::~Identify(){}

Forw::Forw():forwcode(ForwCode::NoForward),receiveCount(0), receivers(0)
{}

Forw::Forw(ForwCode forwcode, int count, std::vector<QString> receivers) :forwcode(forwcode), receiveCount(count)
{
	this->receivers = std::move(receivers);
}

Forw::~Forw(){}

Data::Data():dataType(DataType::Text),dataSize(0),databody("")
{}

Data::Data(DataType datatype, int size, QByteArray body) :dataType(datatype), dataSize(size)
{
	this->databody = std::move(body);
}
	
Data::~Data(){}
