/*
*	一些基本的、常用的头文件加在这里
*	加自定义的头文件时，只要往这个里面加就行了，其他所有源文件一律包含该头文件
*/

#ifndef HEADER_H
#define HEADER_H


#pragma execution_character_set("utf-8")
extern "C" {
#include "Md5.h"
}

#include <assert.h>
#include "TcpClient.h"
#include "configOper.h"
#include "protocol.h"
#include "XmlHelper.h"
#include "XmlConstructor.h"
#include "XmlParser.h"
#include "User.h"

#endif // !HEADER_H