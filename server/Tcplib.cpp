/*
*Author:wk
*Date:2024/8/22
*Description: the class for tcp read and write
*/

#include "Tcplib.h"

bool Readn(const int sockfd, char* buffer, const size_t n)
{
        if(sockfd==-1 || NULL==buffer) return false;
        int nleft,nread,idx;
        nleft=n;
        nread=0;
        idx=0;
        while(nleft>0)
        {
            if((nread = recv(sockfd, buffer+idx, nleft, 0))<=0)
	        {
	            return false;
	        }
	        nleft-=nread;
    	    idx+=nread;
        }
        return true;
}

bool Writen(const int sockfd, char* buffer, const size_t n)
{
        if(sockfd==-1 || NULL==buffer) return false;
        int nleft,nwrite,idx;
        nleft=n;
        nwrite=0;
        idx=0;
        while(nleft>0)
        {
            if((nwrite = send(sockfd, buffer+idx, nleft, 0))<=0)
	        {
	            return false;
	        }
	        nleft-=nwrite;
    	    idx+=nwrite;
        }
        return true;
}


bool TcpRead(int sockfd, char* buffer, int* ibuflen, const int timeout)
{
        if(sockfd==-1 || NULL==buffer || NULL==ibuflen)	return false;
       
        fd_set tmpfd;
        
        FD_ZERO(&tmpfd);
        FD_SET(sockfd,&tmpfd);
        
        struct timeval sttimeout;
        sttimeout.tv_sec=timeout;
        sttimeout.tv_usec=0;
        
        int i;
        if((i=select(sockfd+1,&tmpfd,0,0,&sttimeout))<=0)	
            return false;
        (*ibuflen)=0;
        if(Readn(sockfd,(char*)ibuflen,4)==false)	
            return false;	
        (*ibuflen)=ntohl(*ibuflen);	
        
        if(Readn(sockfd, buffer, (*ibuflen))==false)	
            return false;
        return true;
}

bool TcpWrite(int sockfd, char* buffer, int* ibuflen)
 {
        if(sockfd==-1 || NULL==buffer)	return false;
        
    		fd_set tmpfd;
        
        FD_ZERO(&tmpfd);
        FD_SET(sockfd,&tmpfd);
        
        struct timeval sttimeout;
        sttimeout.tv_sec=5;
        sttimeout.tv_usec=0;
        
        if(select(sockfd+1,0,&tmpfd,0,&sttimeout)<=0)	
            return false;
        int ilen=1;
        if(ibuflen==0)	ilen=strlen(buffer);    
        else ilen=*ibuflen;	
        
        int ilenn=htonl(ilen);	
       
       	char strBufferTmp[ilen+4];	
        memset(strBufferTmp,0,ilen+4);
        memcpy(strBufferTmp,&ilenn,4);	
        memcpy(strBufferTmp+4,buffer,ilen);	
        
        if(Writen(sockfd, strBufferTmp, ilen+4) == false)	return false;
        return true;
}

// 删除字符串左边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteLChar(char *str,const char chr)
{
  if (str == 0) return;
  if (strlen(str) == 0) return;

  char strTemp[strlen(str)+1];

  int iTemp=0;

  memset(strTemp,0,sizeof(strTemp));
  strcpy(strTemp,str);

  while ( strTemp[iTemp] == chr )  iTemp++;

  memset(str,0,strlen(str)+1);

  strcpy(str,strTemp+iTemp);

  return;
}

// 删除字符串右边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteRChar(char *str,const char chr)
{
  if (str == 0) return;
  if (strlen(str) == 0) return;

  int istrlen = strlen(str);

  while (istrlen>0)
  {
    if (str[istrlen-1] != chr) break;

    str[istrlen-1]=0;

    istrlen--;
  }
}


// 删除字符串左右两边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteLRChar(char *str,const char chr)
{
  DeleteLChar(str,chr);
  DeleteRChar(str,chr);
}

// 把字符串中的小写字母转换成大写，忽略不是字母的字符。
// str：待转换的字符串，支持char[]和string两种类型。
void ToUpper(char *str)
{
  if (str == 0) return;

  if (strlen(str) == 0) return;

  int istrlen=strlen(str);

  for (int ii=0;ii<istrlen;ii++)
  {
    if ( (str[ii] >= 'a') && (str[ii] <= 'z') ) str[ii]=str[ii] - 32;
  }
}

void ToUpper(std::string& str)
{
  if (str.empty()) return;

  char strtemp[str.size()+1];

  memset(strtemp,0,sizeof(strtemp));
  strcpy(strtemp,str.c_str());

  ToUpper(strtemp);

  str=strtemp;

  return;
}



bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,char *value,const int ilen)
{
  if (value==0) return false;

  if (ilen>0) memset(value,0,ilen+1);   // 调用者必须保证value的空间足够，否则这里会内存溢出。

  char *start=0,*end=0;
  char m_SFieldName[51],m_EFieldName[51];

  int m_NameLen = strlen(fieldname);
  memset(m_SFieldName,0,sizeof(m_SFieldName));
  memset(m_EFieldName,0,sizeof(m_EFieldName));

  snprintf(m_SFieldName,50,"<%s>",fieldname);
  snprintf(m_EFieldName,50,"</%s>",fieldname);

  start=0; end=0;

  start = (char *)strstr(xmlbuffer,m_SFieldName);

  if (start != 0)
  {
    end   = (char *)strstr(start,m_EFieldName);
  }

  if ((start==0) || (end == 0))
  {
    return false;
  }

  int   m_ValueLen = end - start - m_NameLen - 2 + 1 ;

  if ( ((m_ValueLen-1) <= ilen) || (ilen == 0) )
  {
    strncpy(value,start+m_NameLen+2,m_ValueLen-1); value[m_ValueLen-1]=0;
  }
  else
  {
    strncpy(value,start+m_NameLen+2,ilen); value[ilen]=0;
  }

  DeleteLRChar(value,' ');

  return true;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,bool *value)
{
  if (value==0) return false;

  (*value) = false;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,10) == true)
  {
    ToUpper(strTemp);  // 转换为大写来判断。
    if (strcmp(strTemp,"TRUE")==0) { (*value)=true; return true; }
  }

  return false;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,int *value)
{
  if (value==0) return false;

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = atoi(strTemp); return true;
  }

  return false;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,unsigned int *value)
{
  if (value==0) return false;

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = (unsigned int)atoi(strTemp); return true;
  }

  return false;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,long *value)
{
  if (value==0) return false;

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = atol(strTemp); return true;
  }

  return false;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,unsigned long *value)
{
  if (value==0) return false;

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = (unsigned long)atol(strTemp); return true;
  }

  return false;
}

bool GetXmlBuffer(const char *xmlbuffer,const char *fieldname,double *value)
{
  if (value==0) return false;

  (*value) = 0;

  char strTemp[51];

  memset(strTemp,0,sizeof(strTemp));

  if (GetXmlBuffer(xmlbuffer,fieldname,strTemp,50) == true)
  {
    (*value) = atof(strTemp); return true;
  }

  return false;
}


