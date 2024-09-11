#ifndef SSLHELPER_H
#define SSLHELPER_H


extern "C" {
#include "Md5.h"
}
#include<assert.h>
#include<stdlib.h>
#include<string.h>
class SSLHelper
{
public:
	static void MD5StrEncode(const char* plainText, size_t plainSize, MD5_STR cipher);
};


#endif // !SSLHELPER_H