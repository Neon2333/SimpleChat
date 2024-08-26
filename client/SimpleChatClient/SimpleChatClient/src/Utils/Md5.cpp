#include "../inc/Md5.h"

Md5* Md5::m_md5 = nullptr;

Md5::Md5(){}


Md5* Md5::getInstance()
{
	if (m_md5 == nullptr)
	{
		static std::mutex mtx;
		std::lock_guard<std::mutex> lg(mtx);
		if(m_md5==nullptr)	m_md5 = new Md5();
	}
	return m_md5;
}

Md5::~Md5()
{
	if(m_md5!=nullptr)
		delete m_md5;
}

void Md5::MD5_Calculate()
{
	a = A, b = B, c = C, d = D;

	/* Round 1 */
	FF(a, b, c, d, m_MD5_Buff[0], 7, 0xd76aa478); /**//* 1 */
	FF(d, a, b, c, m_MD5_Buff[1], 12, 0xe8c7b756); /**//* 2 */
	FF(c, d, a, b, m_MD5_Buff[2], 17, 0x242070db); /**//* 3 */
	FF(b, c, d, a, m_MD5_Buff[3], 22, 0xc1bdceee); /**//* 4 */
	FF(a, b, c, d, m_MD5_Buff[4], 7, 0xf57c0faf); /**//* 5 */
	FF(d, a, b, c, m_MD5_Buff[5], 12, 0x4787c62a); /**//* 6 */
	FF(c, d, a, b, m_MD5_Buff[6], 17, 0xa8304613); /**//* 7 */
	FF(b, c, d, a, m_MD5_Buff[7], 22, 0xfd469501); /**//* 8 */
	FF(a, b, c, d, m_MD5_Buff[8], 7, 0x698098d8); /**//* 9 */
	FF(d, a, b, c, m_MD5_Buff[9], 12, 0x8b44f7af); /**//* 10 */
	FF(c, d, a, b, m_MD5_Buff[10], 17, 0xffff5bb1); /**//* 11 */
	FF(b, c, d, a, m_MD5_Buff[11], 22, 0x895cd7be); /**//* 12 */
	FF(a, b, c, d, m_MD5_Buff[12], 7, 0x6b901122); /**//* 13 */
	FF(d, a, b, c, m_MD5_Buff[13], 12, 0xfd987193); /**//* 14 */
	FF(c, d, a, b, m_MD5_Buff[14], 17, 0xa679438e); /**//* 15 */
	FF(b, c, d, a, m_MD5_Buff[15], 22, 0x49b40821); /**//* 16 */

  /* Round 2 */
	GG(a, b, c, d, m_MD5_Buff[1], 5, 0xf61e2562); /**//* 17 */
	GG(d, a, b, c, m_MD5_Buff[6], 9, 0xc040b340); /**//* 18 */
	GG(c, d, a, b, m_MD5_Buff[11], 14, 0x265e5a51); /**//* 19 */
	GG(b, c, d, a, m_MD5_Buff[0], 20, 0xe9b6c7aa); /**//* 20 */
	GG(a, b, c, d, m_MD5_Buff[5], 5, 0xd62f105d); /**//* 21 */
	GG(d, a, b, c, m_MD5_Buff[10], 9, 0x02441453); /**//* 22 */
	GG(c, d, a, b, m_MD5_Buff[15], 14, 0xd8a1e681); /**//* 23 */
	GG(b, c, d, a, m_MD5_Buff[4], 20, 0xe7d3fbc8); /**//* 24 */
	GG(a, b, c, d, m_MD5_Buff[9], 5, 0x21e1cde6); /**//* 25 */
	GG(d, a, b, c, m_MD5_Buff[14], 9, 0xc33707d6); /**//* 26 */
	GG(c, d, a, b, m_MD5_Buff[3], 14, 0xf4d50d87); /**//* 27 */
	GG(b, c, d, a, m_MD5_Buff[8], 20, 0x455a14ed); /**//* 28 */
	GG(a, b, c, d, m_MD5_Buff[13], 5, 0xa9e3e905); /**//* 29 */
	GG(d, a, b, c, m_MD5_Buff[2], 9, 0xfcefa3f8); /**//* 30 */
	GG(c, d, a, b, m_MD5_Buff[7], 14, 0x676f02d9); /**//* 31 */
	GG(b, c, d, a, m_MD5_Buff[12], 20, 0x8d2a4c8a); /**//* 32 */

	/* Round 3 */
	HH(a, b, c, d, m_MD5_Buff[5], 4, 0xfffa3942); /**//* 33 */
	HH(d, a, b, c, m_MD5_Buff[8], 11, 0x8771f681); /**//* 34 */
	HH(c, d, a, b, m_MD5_Buff[11], 16, 0x6d9d6122); /**//* 35 */
	HH(b, c, d, a, m_MD5_Buff[14], 23, 0xfde5380c); /**//* 36 */
	HH(a, b, c, d, m_MD5_Buff[1], 4, 0xa4beea44); /**//* 37 */
	HH(d, a, b, c, m_MD5_Buff[4], 11, 0x4bdecfa9); /**//* 38 */
	HH(c, d, a, b, m_MD5_Buff[7], 16, 0xf6bb4b60); /**//* 39 */
	HH(b, c, d, a, m_MD5_Buff[10], 23, 0xbebfbc70); /**//* 40 */
	HH(a, b, c, d, m_MD5_Buff[13], 4, 0x289b7ec6); /**//* 41 */
	HH(d, a, b, c, m_MD5_Buff[0], 11, 0xeaa127fa); /**//* 42 */
	HH(c, d, a, b, m_MD5_Buff[3], 16, 0xd4ef3085); /**//* 43 */
	HH(b, c, d, a, m_MD5_Buff[6], 23, 0x04881d05); /**//* 44 */
	HH(a, b, c, d, m_MD5_Buff[9], 4, 0xd9d4d039); /**//* 45 */
	HH(d, a, b, c, m_MD5_Buff[12], 11, 0xe6db99e5); /**//* 46 */
	HH(c, d, a, b, m_MD5_Buff[15], 16, 0x1fa27cf8); /**//* 47 */
	HH(b, c, d, a, m_MD5_Buff[2], 23, 0xc4ac5665); /**//* 48 */

	/* Round 4 */
	II(a, b, c, d, m_MD5_Buff[0], 6, 0xf4292244); /**//* 49 */
	II(d, a, b, c, m_MD5_Buff[7], 10, 0x432aff97); /**//* 50 */
	II(c, d, a, b, m_MD5_Buff[14], 15, 0xab9423a7); /**//* 51 */
	II(b, c, d, a, m_MD5_Buff[5], 21, 0xfc93a039); /**//* 52 */
	II(a, b, c, d, m_MD5_Buff[12], 6, 0x655b59c3); /**//* 53 */
	II(d, a, b, c, m_MD5_Buff[3], 10, 0x8f0ccc92); /**//* 54 */
	II(c, d, a, b, m_MD5_Buff[10], 15, 0xffeff47d); /**//* 55 */
	II(b, c, d, a, m_MD5_Buff[1], 21, 0x85845dd1); /**//* 56 */
	II(a, b, c, d, m_MD5_Buff[8], 6, 0x6fa87e4f); /**//* 57 */
	II(d, a, b, c, m_MD5_Buff[15], 10, 0xfe2ce6e0); /**//* 58 */
	II(c, d, a, b, m_MD5_Buff[6], 15, 0xa3014314); /**//* 59 */
	II(b, c, d, a, m_MD5_Buff[13], 21, 0x4e0811a1); /**//* 60 */
	II(a, b, c, d, m_MD5_Buff[4], 6, 0xf7537e82); /**//* 61 */
	II(d, a, b, c, m_MD5_Buff[11], 10, 0xbd3af235); /**//* 62 */
	II(c, d, a, b, m_MD5_Buff[2], 15, 0x2ad7d2bb); /**//* 63 */
	II(b, c, d, a, m_MD5_Buff[9], 21, 0xeb86d391); /**//* 64 */

	A += a;
	B += b;
	C += c;
	D += d;
}

/// <summary>
/// md5����
/// </summary>
/// <param name="buffer">�������ֽ����飬������</param>
/// <param name="len">�ֽ����鳤��</param>
/// <returns></returns>
char* Md5::encode(char* buffer, int len)
{
	unsigned int i = 0;

	//��ȡ�������ݳ��ȣ���λ - �ֽڣ�
	m_FileLen_Byte = len - 1;//����Ҫע���ȥ�ַ���������'\0'ռ��һ���ֽڳ���			

	//����ѭ������ֱ���ļ�������ÿ�� 512 bit �� ÿ�� 64 �ֽڣ�
	for (i = 0; i < m_FileLen_Byte / 64; i++)
	{
		memset(m_MD5_Buff, 0, 64);   						//��ʼ�� MD5_Buff ����Ϊ0
		memcpy(&m_MD5_Buff[0], &m_FileBuff[i * 64], 64);	//�ߵ�λ����ֵ����С��ת����
		MD5_Calculate();								//���������߼�����
	}

	//���һ�鲻��512 bit����λ ��1�� �� ��0��
	memset(m_MD5_Buff, 0, 64);   							//��ʼ�� MD5_Buff�������С16���������ͳ���4�ֽڣ�
	memset(m_MD5_ChangeBuff, 0, 64);						//��ʼ�� MD5_ChangeBuff�������С64���������ͳ���1�ֽڣ�

	memcpy(m_MD5_ChangeBuff, &m_FileBuff[m_FileLen_Byte - (m_FileLen_Byte % 64)], m_FileLen_Byte % 64);

	m_MD5_ChangeBuff[m_FileLen_Byte % 64] = 128;			//���ļ�ĩβ�Ȳ�һ��1���߸�0��ʮ����128�Ķ����Ƽ�1000 0000
	memcpy(&m_MD5_Buff[0], &m_MD5_ChangeBuff[0], 64);		//�ߵ�λ����ֵ����С��ת����


	//�����һ���ֽڣ�128�Ķ����Ƽ�1000 0000���ж���һ�黹��û�п�λ�� �ļ����ǰ�ĳ��ȣ�64bit,��8���ֽڣ�

	//������λ�÷ţ����ٲ�һ��512 bit��������������ļ����ǰ���ȡ�
	if ((m_FileLen_Byte % 64) > 55)		//64 - 1 - 8 = 55
	{
		MD5_Calculate();				//���������߼�����
		memset(m_MD5_Buff, 0, 64);   		//��ʼ�� MD5_Buff ����Ϊ0
	}

	//�����һ������������ԭʼ�ļ����ǰ�ĳ��ȣ���λ - λ bit��
	m_FileLen_Bit[1] = m_FileLen_Byte / 0x20000000;
	m_FileLen_Bit[0] = (m_FileLen_Byte % 0x20000000) * 8;	//��һ��Ҫע���С��ת������ǰ���ת����ʽ��̫һ��

	memcpy(&m_MD5_Buff[14], m_FileLen_Bit, 8);				//ĩβ����ԭ�ļ���bit���ȣ��ļ����ǰ�ĳ��ȣ���λ - bit����

	MD5_Calculate();

	memcpy(&m_MD5_Data[0], &A, 4);		//�ߵ�λ����ֵ
	memcpy(&m_MD5_Data[4], &B, 4);		//�ߵ�λ����ֵ
	memcpy(&m_MD5_Data[8], &C, 4);		//�ߵ�λ����ֵ
	memcpy(&m_MD5_Data[12], &D, 4);		//�ߵ�λ����ֵ

	return m_MD5_Data;
}

