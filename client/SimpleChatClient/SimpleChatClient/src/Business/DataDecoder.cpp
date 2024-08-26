#include"../inc/DataDecoder.h"

DataDecoder::DataDecoder()
{
}

DataDecoder::~DataDecoder()
{
}

bool DataDecoder::ParseMsgTypeXml(const QByteArray& msg, MsgType* msgtype)
{
	const char* msgTmp = msg.data();
	int size = msg.length();
	
	return GetXmlBuffer(msgTmp, "msgtype", reinterpret_cast<int*>(msgtype));;
}

bool DataDecoder::ParseHeartBeatXml(const QByteArray& msg, RetCode* retcode)
{
	const char* msgTmp = msg.data();
	return GetXmlBuffer(msgTmp, "retcode", reinterpret_cast<int*>(retcode));
}

bool DataDecoder::ParseAckXml(const QByteArray& msg, BizCode* bizcode, DataType* datatype, int* receivesize)
{
	const char* msgTmp = msg.data();
	if (!GetXmlBuffer(msgTmp, "bizcode", reinterpret_cast<int*>(bizcode)))
		return false;
	if (!GetXmlBuffer(msgTmp, "datatype", reinterpret_cast<int*>(datatype)))
		return false;
	if (!GetXmlBuffer(msgTmp, "receivesize", reinterpret_cast<int*>(receivesize)))
		return false;

	return true;
}

bool DataDecoder::ParseResponseXml(const QByteArray msg, BizCode* bizcode, RetCode* retcode, Data* data)
{
	const char* msgTmp = msg.data();
	if (!GetXmlBuffer(msgTmp, "bizcode", reinterpret_cast<int*>(bizcode)))
		return false;
	if (!GetXmlBuffer(msgTmp, "retcode", reinterpret_cast<int*>(retcode)))
		return false;

	if (data == nullptr)	return true;

	if (!GetXmlBuffer(msgTmp, "datatype", reinterpret_cast<int*>(&(data->dataType))))
		return false;
	if (!GetXmlBuffer(msgTmp, "datasize", reinterpret_cast<int*>(&(data->dataSize))))
		return false;
	if (!GetXmlBuffer(msgTmp, "databody", reinterpret_cast<int*>(&(data->databody))))
		return false;

	return true;
}
