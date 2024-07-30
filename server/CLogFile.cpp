#include "CLogFile.h"


CLogFile::CLogFile(const long MaxLogSize)
{
  m_tracefp = 0;
  memset(m_filename,0,sizeof(m_filename));
  memset(m_openmode,0,sizeof(m_openmode));
  m_bBackup=true;
  m_bEnBuffer=false;
  m_MaxLogSize=MaxLogSize;
  if (m_MaxLogSize<10) m_MaxLogSize=10;
}

CLogFile::~CLogFile()
{
  Close();
}

void CLogFile::Close()
{
  if (m_tracefp != 0) { fclose(m_tracefp); m_tracefp=0; }

  memset(m_filename,0,sizeof(m_filename));
  memset(m_openmode,0,sizeof(m_openmode));
  m_bBackup=true;
  m_bEnBuffer=false;
}

// ����־�ļ���
// filename����־�ļ�����������þ���·��������ļ����е�Ŀ¼�����ڣ����ȴ���Ŀ¼��
// openmode����־�ļ��Ĵ򿪷�ʽ����fopen�⺯�����ļ��ķ�ʽ��ͬ��ȱʡֵ��"a+"��
// bBackup���Ƿ��Զ��л���true-�л���false-���л����ڶ���̵ķ�������У����������й���һ����־�ļ���bBackup����Ϊfalse��
// bEnBuffer���Ƿ������ļ�������ƣ�true-���ã�false-�����ã�������û���������ôд����־�ļ��е����ݲ�������д���ļ���ȱʡ�ǲ����á�
bool CLogFile::Open(const char *filename,const char *openmode,bool bBackup,bool bEnBuffer)
{
  // ����ļ�ָ���Ǵ򿪵�״̬���ȹر�����
  Close();

  strcpy(m_filename,filename);
  m_bEnBuffer=bEnBuffer;
  m_bBackup=bBackup;
  if (openmode==0) strcpy(m_openmode,"a+");
  else strcpy(m_openmode,openmode);

  if ((m_tracefp=fopen(m_filename,m_openmode)) == 0) return false;

  return true;
}


void timetostr(const time_t ltime,char *stime,const char *fmt)
{
  if (stime==0) return;

  strcpy(stime,"");

  struct tm sttm = *localtime ( &ltime ); 

  sttm.tm_year=sttm.tm_year+1900;
  sttm.tm_mon++;

  if (fmt==0)
  {
    snprintf(stime,20,"%04u-%02u-%02u %02u:%02u:%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour,
                    sttm.tm_min,sttm.tm_sec);
    return;
  }

  if (strcmp(fmt,"yyyy-mm-dd hh24:mi:ss") == 0)
  {
    snprintf(stime,20,"%04u-%02u-%02u %02u:%02u:%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour,
                    sttm.tm_min,sttm.tm_sec);
    return;
  }

  if (strcmp(fmt,"yyyy-mm-dd hh24:mi") == 0)
  {
    snprintf(stime,17,"%04u-%02u-%02u %02u:%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour,
                    sttm.tm_min);
    return;
  }

  if (strcmp(fmt,"yyyy-mm-dd hh24") == 0)
  {
    snprintf(stime,14,"%04u-%02u-%02u %02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour);
    return;
  }

  if (strcmp(fmt,"yyyy-mm-dd") == 0)
  {
    snprintf(stime,11,"%04u-%02u-%02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday); 
    return;
  }

  if (strcmp(fmt,"yyyy-mm") == 0)
  {
    snprintf(stime,8,"%04u-%02u",sttm.tm_year,sttm.tm_mon); 
    return;
  }

  if (strcmp(fmt,"yyyymmddhh24miss") == 0)
  {
    snprintf(stime,15,"%04u%02u%02u%02u%02u%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour,
                    sttm.tm_min,sttm.tm_sec);
    return;
  }

  if (strcmp(fmt,"yyyymmddhh24mi") == 0)
  {
    snprintf(stime,13,"%04u%02u%02u%02u%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour,
                    sttm.tm_min);
    return;
  }

  if (strcmp(fmt,"yyyymmddhh24") == 0)
  {
    snprintf(stime,11,"%04u%02u%02u%02u",sttm.tm_year,
                    sttm.tm_mon,sttm.tm_mday,sttm.tm_hour);
    return;
  }

  if (strcmp(fmt,"yyyymmdd") == 0)
  {
    snprintf(stime,9,"%04u%02u%02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday); 
    return;
  }

  if (strcmp(fmt,"hh24miss") == 0)
  {
    snprintf(stime,7,"%02u%02u%02u",sttm.tm_hour,sttm.tm_min,sttm.tm_sec); 
    return;
  }

  if (strcmp(fmt,"hh24mi") == 0)
  {
    snprintf(stime,5,"%02u%02u",sttm.tm_hour,sttm.tm_min); 
    return;
  }

  if (strcmp(fmt,"hh24") == 0)
  {
    snprintf(stime,3,"%02u",sttm.tm_hour); 
    return;
  }

  if (strcmp(fmt,"mi") == 0)
  {
    snprintf(stime,3,"%02u",sttm.tm_min); 
    return;
  }
}

void LocalTime(char *stime,const char *fmt,const int timetvl)
{
  if (stime==0) return;

  time_t  timer;

  time( &timer ); timer=timer+timetvl;

  timetostr(timer,stime,fmt);
}


bool CLogFile::BackupLogFile()
{
  if (m_tracefp == 0) return false;

  // ������
  if (m_bBackup == false) return true;

  fseek(m_tracefp,0L,2);

  if (ftell(m_tracefp) > m_MaxLogSize*1024*1024)	//�����ļ���С(Byte)
  {
    fclose(m_tracefp); m_tracefp=0;

    char strLocalTime[21];
    memset(strLocalTime,0,sizeof(strLocalTime));
    LocalTime(strLocalTime,"yyyymmddhh24miss");	//��ȡʱ��洢��strLocalTime

    char bak_filename[301];
    memset(bak_filename,0,sizeof(bak_filename));
    snprintf(bak_filename,300,"%s.%s",m_filename,strLocalTime);
    rename(m_filename,bak_filename);	//����ǰ��־�ļ�����Ϊ������.ʱ��

    if ((m_tracefp=fopen(m_filename,m_openmode)) == 0) return false;	//���´�����־�ļ�
  }

  return true;
}

bool CLogFile::Write(const char *fmt,...)
{
  if (m_tracefp == 0) return false;

  if (BackupLogFile() == false) return false;

  char strtime[20]; LocalTime(strtime);

  va_list ap;
  va_start(ap,fmt);
  fprintf(m_tracefp,"%s ",strtime);
  vfprintf(m_tracefp,fmt,ap);
  va_end(ap);

  if (m_bEnBuffer==false) fflush(m_tracefp);

  return true;
}

bool CLogFile::WriteEx(const char *fmt,...)
{
  if (m_tracefp == 0) return false;

  va_list ap;
  va_start(ap,fmt);
  vfprintf(m_tracefp,fmt,ap);
  va_end(ap);

  if (m_bEnBuffer==false) fflush(m_tracefp);

  return true;
}