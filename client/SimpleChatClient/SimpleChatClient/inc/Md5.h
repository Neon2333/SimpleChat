#ifndef MD5_H
#define MD5_H
#include<stdlib.h>
#include<stdio.h>
#include<cstring>

#define F(x, y, z) 	(((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) 	(((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) 	((x) ^ (y) ^ (z))
#define I(x, y, z) 	((y) ^ ((x) | (~z)))

#define RL(x, y) 	(((x) << (y)) | ((x) >> (32 - (y))))  //x����ѭ����yλ

#define FF(a, b, c, d, x, s, ac) a = b + (RL((a + F(b,c,d) + x + ac),s))
#define GG(a, b, c, d, x, s, ac) a = b + (RL((a + G(b,c,d) + x + ac),s))
#define HH(a, b, c, d, x, s, ac) a = b + (RL((a + H(b,c,d) + x + ac),s))
#define II(a, b, c, d, x, s, ac) a = b + (RL((a + I(b,c,d) + x + ac),s))


/// <summary>
/// md5������
/// </summary>
class Md5
{
private:
	//�ĸ�32λ���ӱ����ĳ�ʼ��ֵ
	unsigned int A = 0x67452301;
	unsigned int B = 0xefcdab89;
	unsigned int C = 0x98badcfe;
	unsigned int D = 0x10325476;

	unsigned int a, b, c, d = 0;			//4���߼����������ӱ����Ĺ�����

	char* m_FileBuff;				//�洢�������ַ���
	unsigned int m_FileLen_Byte;			//�ļ����ǰ�ĳ��ȣ���λ - �ֽڣ�

	unsigned int m_FileLen_Bit[2];		//�ļ����ǰ�ĳ��ȣ���λ - λ bit��

	char  m_MD5_ChangeBuff[64];	//��ʱ������ - ���ڲ�λ����
	unsigned int m_MD5_Buff[16];			//��ʱ������ - ����ÿ������װÿ��512 bit����

	char  m_MD5_Data[16];			//���ռ����� - �ļ���MD5ֵ

	static Md5* m_md5;
	Md5();
	void MD5_Calculate();

public:
	~Md5();
	static Md5* md5();
	char* encode(char* buffer, int len);
};






#endif // !MD5_H
