#include "SSLHelper.h"

void SSLHelper::MD5StrEncode(const char* plainText, size_t plainSize, MD5_STR cipher)
{
    assert(0 == MD5Test());
    MD5 digest; //��ֵMD5
    char* buffer = (char*)malloc(plainSize);
    assert(buffer != NULL);
    memset(buffer, 0, plainSize);
    memcpy(buffer, plainText, plainSize);
    MD5Buffer(buffer, plainSize, digest); //buffer->digest
    if (buffer != NULL) free(buffer);

    MD5String(digest, cipher);   //����ֵMD5ת�����ַ���MD5��digest->mdstr
}

//AES���ַ������ܽ��ܣ�Ӧ����xmlstr�ϣ����ܺ��ٷ��͡�