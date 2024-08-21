/*
*Author:
*Date:
*Description: the class for log
*/

#ifndef CLOGFILE_H
#define CLOGFILE_H

// 日志文件操作类
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

void LocalTime(char *stime,const char *fmt=0,const int timetvl=0);
void timetostr(const time_t ltime,char *stime,const char *fmt=0);


class CLogFile
{
public:
  FILE   *m_tracefp;           // 日志文件指针。
  char    m_filename[301];     // 日志文件名，建议采用绝对路径。
  char    m_openmode[11];      // 日志文件的打开方式，一般采用"a+"。
  bool    m_bEnBuffer;         // 写入日志时，是否启用操作系统的缓冲机制，缺省不启用。
  long    m_MaxLogSize;        // 最大日志文件的大小，单位M，缺省100M。
  bool    m_bBackup;           // 是否自动切换，日志文件大小超过m_MaxLogSize将自动切换，缺省启用。

    
  // MaxLogSize：最大日志文件的大小，单位M，缺省100M，最小为10M。
  CLogFile(const long MaxLogSize=100); 

  // 打开日志文件。
  // filename：日志文件名，建议采用绝对路径，如果文件名中的目录不存在，就先创建目录。
  // openmode：日志文件的打开方式，与fopen库函数打开文件的方式相同，缺省值是"a+"。
  // bBackup：是否自动切换，true-切换，false-不切换，在多进程的服务程序中，如果多个进行共用一个日志文件，bBackup必须为false。
  // bEnBuffer：是否启用文件缓冲机制，true-启用，false-不启用，如果启用缓冲区，那么写进日志文件中的内容不会立即写入文件，缺省是不启用。
  bool Open(const char *filename,const char *openmode=0,bool bBackup=true,bool bEnBuffer=false);

  // 如果日志文件大于100M，就把当前的日志文件备份成历史日志文件，切换成功后清空当前日志文件的内容。
  // 备份后的文件会在日志文件名后加上日期时间。
  // 注意，在多进程的程序中，日志文件不可切换，多线的程序中，日志文件可以切换。
  bool BackupLogFile();

  // 把内容写入日志文件，fmt是可变参数，使用方法与printf库函数相同。
  // Write方法会写入当前的时间，WriteEx方法不写时间，WriteUseMtx写日志行为加锁
  bool Write(const char *fmt,...);
  bool WriteEx(const char *fmt,...);
  //bool WriteUseMtx(const char *fmt,...);
  // 关闭日志文件
  void Close();

  ~CLogFile();  // 析构函数会调用Close方法。
};

#endif