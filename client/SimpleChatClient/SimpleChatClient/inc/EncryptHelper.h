#ifndef ENCRYPTHELPER_H
#define ENCRYPTHELPER_H

extern "C" {
#include "Md5.h"
}
#include<assert.h>
#include<stdlib.h>
#include<string.h>

class EncryptHelper
{
public:
	static void MD5StrEncode(const char* plainText, size_t plainSize, MD5_STR cipher);

};

#endif // !ENCRYPTHELPER_H
