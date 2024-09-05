#include "EncryptHelper.h"

void EncryptHelper::MD5StrEncode(const char* plainText, size_t plainSize, MD5_STR cipher)
{
    assert(0 == MD5Test());
    MD5 digest; //数值MD5
    char* buffer = (char*)malloc(plainSize);
    assert(buffer != NULL);
    memset(buffer, 0, plainSize);
    memcpy(buffer, plainText, plainSize);
    MD5Buffer(buffer, plainSize, digest); //buffer->digest
    if (buffer != NULL) free(buffer);

    MD5String(digest, cipher);   //将数值MD5转换成字符串MD5，digest->mdstr
}
