#include "../../inc/XmlHelper.h"

// ɾ���ַ������ָ�����ַ���
// str����������ַ�����
// chr����Ҫɾ�����ַ���
void DeleteLChar(char* str, const char chr)
{
    if (str == 0) return;
    if (strlen(str) == 0) return;

    char* strTemp = (char*)malloc(strlen(str) + 1);

    int iTemp = 0;

    memset(strTemp, 0, sizeof(strTemp));
    strcpy(strTemp, str);

    while (strTemp[iTemp] == chr)  iTemp++;

    memset(str, 0, strlen(str) + 1);

    strcpy(str, strTemp + iTemp);

    free(strTemp);

    return;
}

// ɾ���ַ����ұ�ָ�����ַ���
// str����������ַ�����
// chr����Ҫɾ�����ַ���
void DeleteRChar(char* str, const char chr)
{
    if (str == 0) return;
    if (strlen(str) == 0) return;

    int istrlen = strlen(str);

    while (istrlen > 0)
    {
        if (str[istrlen - 1] != chr) break;

        str[istrlen - 1] = 0;

        istrlen--;
    }
}


// ɾ���ַ�����������ָ�����ַ���
// str����������ַ�����
// chr����Ҫɾ�����ַ���
void DeleteLRChar(char* str, const char chr)
{
    DeleteLChar(str, chr);
    DeleteRChar(str, chr);
}


// ���ַ����е�Сд��ĸת���ɴ�д�����Բ�����ĸ���ַ���
// str����ת�����ַ�����֧��char[]��string�������͡�
void ToUpper(char* str)
{
    if (str == 0) return;

    if (strlen(str) == 0) return;

    int istrlen = strlen(str);

    for (int ii = 0; ii < istrlen; ii++)
    {
        if ((str[ii] >= 'a') && (str[ii] <= 'z')) str[ii] = str[ii] - 32;
    }
}

void ToUpper(std::string& str)
{
    if (str.empty()) return;

    char* strtmp = (char*)malloc(str.size() + 1);

    memset(strtmp, 0, sizeof(strtmp));
    strcpy(strtmp, str.c_str());

    ToUpper(strtmp);

    str = strtmp;
    free(strtmp);

    return;
}



bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, char* value, const int ilen)
{
    if (value == 0) return false;

    if (ilen > 0) memset(value, 0, ilen + 1);   // �����߱��뱣֤value�Ŀռ��㹻������������ڴ������

    char* start = 0, * end = 0;
    char m_SFieldName[51], m_EFieldName[51];

    int m_NameLen = strlen(fieldname);
    memset(m_SFieldName, 0, sizeof(m_SFieldName));
    memset(m_EFieldName, 0, sizeof(m_EFieldName));

    snprintf(m_SFieldName, 50, "<%s>", fieldname);
    snprintf(m_EFieldName, 50, "</%s>", fieldname);

    start = 0; end = 0;

    start = (char*)strstr(xmlbuffer, m_SFieldName);

    if (start != 0)
    {
        end = (char*)strstr(start, m_EFieldName);
    }

    if ((start == 0) || (end == 0))
    {
        return false;
    }

    int   m_ValueLen = end - start - m_NameLen - 2 + 1;

    if (((m_ValueLen - 1) <= ilen) || (ilen == 0))
    {
        strncpy(value, start + m_NameLen + 2, m_ValueLen - 1); value[m_ValueLen - 1] = 0;
    }
    else
    {
        strncpy(value, start + m_NameLen + 2, ilen); value[ilen] = 0;
    }

    DeleteLRChar(value, ' ');

    return true;
}

bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, bool* value)
{
    if (value == 0) return false;

    (*value) = false;

    char strTemp[51];

    memset(strTemp, 0, sizeof(strTemp));

    if (GetXmlBuffer(xmlbuffer, fieldname, strTemp, 10) == true)
    {
        ToUpper(strTemp);  // ת��Ϊ��д���жϡ�
        if (strcmp(strTemp, "TRUE") == 0) { (*value) = true; return true; }
    }

    return false;
}

bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, int* value)
{
    if (value == 0) return false;

    (*value) = 0;

    char strTemp[51];

    memset(strTemp, 0, sizeof(strTemp));

    if (GetXmlBuffer(xmlbuffer, fieldname, strTemp, 50) == true)
    {
        (*value) = atoi(strTemp); return true;
    }

    return false;
}

bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, unsigned int* value)
{
    if (value == 0) return false;

    (*value) = 0;

    char strTemp[51];

    memset(strTemp, 0, sizeof(strTemp));

    if (GetXmlBuffer(xmlbuffer, fieldname, strTemp, 50) == true)
    {
        (*value) = (unsigned int)atoi(strTemp); return true;
    }

    return false;
}

bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, long* value)
{
    if (value == 0) return false;

    (*value) = 0;

    char strTemp[51];

    memset(strTemp, 0, sizeof(strTemp));

    if (GetXmlBuffer(xmlbuffer, fieldname, strTemp, 50) == true)
    {
        (*value) = atol(strTemp); return true;
    }

    return false;
}

bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, unsigned long* value)
{
    if (value == 0) return false;

    (*value) = 0;

    char strTemp[51];

    memset(strTemp, 0, sizeof(strTemp));

    if (GetXmlBuffer(xmlbuffer, fieldname, strTemp, 50) == true)
    {
        (*value) = (unsigned long)atol(strTemp); return true;
    }

    return false;
}

bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, double* value)
{
    if (value == 0) return false;

    (*value) = 0;

    char strTemp[51];

    memset(strTemp, 0, sizeof(strTemp));

    if (GetXmlBuffer(xmlbuffer, fieldname, strTemp, 50) == true)
    {
        (*value) = atof(strTemp); return true;
    }

    return false;
}

