#pragma once
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#if defined(_WIN16) || defined(_WIN32) || defined(WIN64)
const bool isLinuxOS = false;
#elif defined(__linux__)
const bool isLinuxOS = true;// linux OS 
#define sprintf_s(_Buffer, _Format, ...) sprintf(_Buffer, _Format,__VA_ARGS__)
#define fopen_s(_Stream, _FileName, _Mode) *_Stream = fopen(_FileName,_Mode)
#endif

#define MAX_ARRAY_LEN (1024 * 512) //buffer size


/*
* function is similar to GetPrivateProfileString(win32)
*
* param
*   lpAppName       section name
*   lpKeyName       key name
*   lpDefault       default value
*   pReturnedString buffer string
*   nSize           size of buffer
*   lpFileName      ini file
* return
*   The return value is the number of characters copied to the buffer
* comment
*   can read [\r\n](line feed code) and [\n]
*/
int GetPrivateProfileStringLinux(const char* pAppName, const char* pKeyName, const char* lpDefault, char* pReturnedString, unsigned long nSize, const char* pFileName);
/*
* function is similar to GetPrivateProfileInt(win32)
*
* param
*   lpAppName       section name
*   lpKeyName       key name
*   nDefault        default value
*   lpFileName      ini file
* return
*   number(int) read from ini-file
*
*/
int GetPrivateProfileIntLinux(const char* pAppName, const char* pKeyName, int nDefault, const char* pFileName);