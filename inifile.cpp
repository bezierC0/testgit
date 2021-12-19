#include "inifile.h"
char strBuf[MAX_ARRAY_LEN] = { '0' };// buffer of read ini
int GetPrivateProfileStringLinux(const char* pAppName, const char* pKeyName, const char* lpDefault,
	char* pReturnedString, unsigned long nSize, const char* pFileName) {

	if (pReturnedString && strlen(pReturnedString))
		memset(pReturnedString, 0, nSize);

	FILE* fp;
	int hasSectionFlag = 0;
	char sSection[256], * sTempValue;

	// open ini file
	fopen_s(&fp, pFileName, "r");
	if (!fp) {
		return -1;
	}

	// section string [XXX]
	sprintf_s(sSection, "[%s]", pAppName);

	while (NULL != fgets(strBuf, MAX_ARRAY_LEN, fp))
	{
		if (0 == strncmp("//", strBuf, 2)) continue;// comment[//]
		if ('#' == strBuf[0])              continue;// comment[#]
		if (hasSectionFlag && '[' == strBuf[0]) break;

		sTempValue = strchr(strBuf, '=');
		if ((NULL != sTempValue) && (hasSectionFlag)) {
			// key and value
			if (0 == strncmp(pKeyName, strBuf, sTempValue - strBuf)) {
				int line_feed_code = 0;//count
				if ('\n' == strBuf[strlen(strBuf) - 1]) {
					line_feed_code = 1;
					// windows CR+LF
					if (isLinuxOS) {
						if ('\r' == strBuf[strlen(strBuf) - 2]) {
							line_feed_code = 2;
						}
					}
					// end code 
					strBuf[strlen(strBuf) - line_feed_code] = '\0';
				}
				fclose(fp);
				// an empty string value
				if(strlen(sTempValue) == 1)
					memcpy(pReturnedString, lpDefault, strlen(lpDefault));
				else
					memcpy(pReturnedString, sTempValue + 1, strlen(sTempValue) - 1);
				return (int)strlen(pReturnedString);
			}
		}
		else {
			// read section 
			if (strlen(strBuf) - 1 > 0) {
				if (0 == strncmp(sSection, strBuf, strlen(strBuf) - 1)) {
					hasSectionFlag = 1;
				}
				else {
					// windows CR+LF
					if (isLinuxOS) {
						if (0 == strncmp(sSection, strBuf, strlen(strBuf) - 2))
							hasSectionFlag = 1;
					}
				}
			}
		}
	}
	fclose(fp);

	memcpy(pReturnedString, lpDefault, strlen(lpDefault));
	return (int)strlen(pReturnedString);
}

int GetPrivateProfileIntLinux(const char* pAppName, const char* pKeyName, int nDefault, const char* pFileName)
{
	char buf[1024] = { 0 };

	if (GetPrivateProfileStringLinux(pAppName, pKeyName, "", buf, 1024, pFileName) <= 0)
		return nDefault;

	if (strlen(buf) == 0)
		return nDefault;

	return atoi(buf);
}