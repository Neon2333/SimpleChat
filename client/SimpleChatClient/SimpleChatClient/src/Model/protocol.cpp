#include "../../inc/protocol.h"

#define ACCOUNT_SIZE 20
#define PASSWORD_SIZE 20
#define TOKEN_SIZE 50


Identify::Identify():account(""), password(""), token("")
{}

Identify::Identify(const Identify & another)
{
	this->account = another.account;
	this->password = another.password;
	this->token = another.token;
}

Identify& Identify::operator=(const Identify& another)
{
	if (this != &another)
	{
		this->account = another.account;
		this->password = another.password;
		this->token = another.token;
	}
	return *this;
}

Identify::Identify(QByteArray account, QByteArray password, QByteArray token) :account(account), password(password), token(token)
{}

Identify::Identify(const Identify&& another)
{
	this->account = std::move(another.account);
	this->password = std::move(another.password);
	this->token = std::move(another.token);
}

Identify& Identify::operator=(const Identify&& another)
{
	if (this != &another)
	{
		this->account = std::move(another.account);
		this->password = std::move(another.password);
		this->token = std::move(another.token);
	}
	
	return *this;
}

Identify::~Identify(){}

void Identify::setAccount(QByteArray& account)
{
	this->account = std::move(account);
}

void Identify::setPassword(QByteArray& password)
{
	this->password = std::move(password);
}

void Identify::setToken(QByteArray& token)
{
	this->token = std::move(token);
}

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
