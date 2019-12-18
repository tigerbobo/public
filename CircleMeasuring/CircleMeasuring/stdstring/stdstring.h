#pragma once

#include <tchar.h>
#include <sstream>

#ifdef UNICODE
#define stdcout	std::wcout
#define stdstring std::wstring
#define stdstringstream std::wstringstream
#else
#define stdcout	std::cout
#define stdstring std::string
#define stdstringstream std::stringstream
#endif

extern stdstring formatstring(stdstring strFormat, ...);

extern stdstring trimleft(stdstring string, stdstring trim = _T(" \r\n\t"));
extern stdstring trimright(stdstring string, stdstring trim = _T(" \r\n\t"));
extern stdstring trimstring(stdstring string, stdstring trim = _T(" \r\n\t"));

extern void splitstring(stdstring &sub, stdstring string, int index, TCHAR delim);

extern void unicode2asc(std::wstring input, std::string &output);
extern void asc2unicode(std::string input, std::wstring &output);

class CStringEncrypt919
{
public:
	CStringEncrypt919(unsigned char key[9]);
	~CStringEncrypt919(void);

private:
	unsigned char m_key[9];
public:
	stdstring encrypt(stdstring input);
	stdstring decrypt(stdstring input);
};
