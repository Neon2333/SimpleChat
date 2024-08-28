#ifndef DATADECODER_H
#define DATADECODER_H

#include<QByteArray>
#include<QString>
#include "Header.h"

class DataDecoder
{
public:
	DataDecoder();
	~DataDecoder();

	bool ParseMsgTypeXml(const QByteArray& msg, MsgType* msgtype);
	bool ParseHeartBeatXml(const QByteArray& msg, RetCode* retcode);
	bool ParseAckXml(const QByteArray& msg, BizCode* bizcode, DataType* datatype, int* receivesize);
	bool ParseResponseXml(const QByteArray msg, BizCode* bizcode, RetCode* retcode, Data* data=nullptr);

};


#endif // !DATADECODER_H


