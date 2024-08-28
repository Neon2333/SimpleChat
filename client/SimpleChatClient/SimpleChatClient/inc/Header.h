/*
*	一些基本的、常用的头文件加在这里
*	加自定义的头文件时，只要往这个里面加就行了，其他所有源文件一律包含该头文件
*/

#pragma once
#pragma execution_character_set("utf-8")
extern "C" {
#include "Md5.h"
}

#include "protocol.h"
#include "TcpClient.h"
#include "XmlHelper.h"
#include <assert.h>