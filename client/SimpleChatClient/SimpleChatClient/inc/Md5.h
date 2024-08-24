#ifndef MD5_H
#define MD5_H
#include<stdlib.h>
#include<stdio.h>
#include<cstring>

#define F(x, y, z) 	(((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) 	(((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) 	((x) ^ (y) ^ (z))
#define I(x, y, z) 	((y) ^ ((x) | (~z)))

#define RL(x, y) 	(((x) << (y)) | ((x) >> (32 - (y))))  //x向左循环移y位

#define FF(a, b, c, d, x, s, ac) a = b + (RL((a + F(b,c,d) + x + ac),s))
#define GG(a, b, c, d, x, s, ac) a = b + (RL((a + G(b,c,d) + x + ac),s))
#define HH(a, b, c, d, x, s, ac) a = b + (RL((a + H(b,c,d) + x + ac),s))
#define II(a, b, c, d, x, s, ac) a = b + (RL((a + I(b,c,d) + x + ac),s))


/// <summary>
/// md5加密类
/// </summary>
class Md5
{
private:
	//四个32位链接变量的初始化值
	unsigned int A = 0x67452301;
	unsigned int B = 0xefcdab89;
	unsigned int C = 0x98badcfe;
	unsigned int D = 0x10325476;

	unsigned int a, b, c, d = 0;			//4轮逻辑计算中链接变量的过程量

	char* m_FileBuff;				//存储待加密字符串
	unsigned int m_FileLen_Byte;			//文件填充前的长度（单位 - 字节）

	unsigned int m_FileLen_Bit[2];		//文件填充前的长度（单位 - 位 bit）

	char  m_MD5_ChangeBuff[64];	//临时缓存区 - 用于补位操作
	unsigned int m_MD5_Buff[16];			//临时缓存区 - 用于每次运算装每组512 bit数据

	char  m_MD5_Data[16];			//最终计算结果 - 文件的MD5值

	static Md5* m_md5;
	Md5();
	void MD5_Calculate();

public:
	~Md5();
	static Md5* md5();
	char* encode(char* buffer, int len);
};






#endif // !MD5_H
