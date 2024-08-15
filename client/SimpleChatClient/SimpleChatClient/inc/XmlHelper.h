#ifndef TCPLIB_H
#define TCPLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <signal.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

void DeleteLChar(char* str, const char chr);
void DeleteRChar(char* str, const char chr);
void DeleteLRChar(char* str, const char chr);
void ToUpper(char* str);
void ToUpper(std::string& str);
bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, char* value, const int ilen=0);
bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, bool* value);
bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, int* value);
bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, unsigned int* value);
bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, long* value);
bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, unsigned long* value);
bool GetXmlBuffer(const char* xmlbuffer, const char* fieldname, double* value);

#endif