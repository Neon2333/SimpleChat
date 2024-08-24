#ifndef PROTOCOL_H
#define	PROTOCOL_H

/// <summary>
/// 协议（后续可写入配置文件）
/// </summary>


enum class MsgType
{
	heartbeat = 0,
	request,
	response,
	ack
};

enum class BizCode
{
	signup=0,
	login,
	logout,
	chat
};

enum class ForwCode
{
	noforward = 0,
	forwardtoall,
	forwardtoone,
	forwardtogroup
};

enum class DataType
{
	text = 0,
	image_png=10,
	audio_mp3=20,
	video_mp4=30
};

enum class RetCode
{
	failed=-1,
	success=0
};

struct Data
{
	char[]
};


#endif
