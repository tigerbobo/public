#include "stdafx.h"
#include "stdstring.h"

#include <memory>
#include <stdarg.h>
#include <algorithm>

stdstring formatstring(stdstring strFormat, ...)
{
	va_list args;
	TCHAR buffer[2048] = { 0 };

	va_start(args, strFormat);
	_vstprintf_s(buffer, _countof(buffer), strFormat.c_str(), args);
	va_end(args);

	return stdstring(buffer);
}

stdstring trimleft(stdstring string, stdstring trim)
{
	string.erase(0, string.find_first_not_of(trim));
	return string;
}

stdstring trimright(stdstring string, stdstring trim)
{
	string.erase(string.find_last_not_of(trim) + 1);
	return string;
}

stdstring trimstring(stdstring string, stdstring trim)
{
	string = trimleft(string, trim);
	string = trimright(string, trim);

	return string;
}

void splitstring(stdstring &substring, stdstring string, int index, TCHAR separator)
{
	intptr_t find, result, offset;

	find = 0;
	offset = 0;
	substring = _T("");

	while (true)
	{
		result = string.find(separator, offset);
		if (result >= 0)
			find = find + 1;

		if ((find == index + 1) || ((-1 == result) && (find == index)))
		{
			substring = string.substr(offset, result - offset);
			break;
		}
		else
			offset = result + 1;

		if (-1 == result)
			break;
	}
}

void unicode2asc(std::wstring input, std::string &output)
{
	char *buffer;
	mbstate_t mbstate;
	std::shared_ptr<char> ptr;
	size_t length, count_converted;
	const wchar_t *wcsindirectstring = input.c_str();

	length = (input.length() + 1) * sizeof(wcsindirectstring[0]);
	buffer = new char[length];
	
	buffer[0] = 0;
	ptr.reset(buffer);

	::memset((void*)&mbstate, 0, sizeof(mbstate));
	wcsrtombs_s(&count_converted, buffer, length, &wcsindirectstring, input.length(), &mbstate);

	output = buffer;
}

void asc2unicode(std::string input, std::wstring &output)
{
	wchar_t *buffer;
	std::shared_ptr<wchar_t> ptr;
	size_t length, count_converted;

	length = input.length() + 1;
	buffer = new wchar_t[length];

	buffer[0] = 0;
	ptr.reset(buffer);

	mbstowcs_s(&count_converted, buffer, length, input.c_str(), length - 1);

	output = buffer;
}

CStringEncrypt919::CStringEncrypt919(unsigned char key[9])
{
	memcpy_s(m_key, 9, key, 9);
}

CStringEncrypt919::~CStringEncrypt919(void)
{
}

stdstring CStringEncrypt919::encrypt(stdstring input)
{
	unsigned int value;
	TCHAR buffer[10] = {0};
	size_t i, length, index;
	stdstring result = _T("");

	index = 0;
	length = input.length();

	for (i = 0; i < length; i++)
	{
		buffer[0] = 0;
		value = input.at(i) * m_key[index++];

		_stprintf_s(buffer, 10, _T("%04x"), value);
		result += buffer;

		if (9 == index)
			index = 0;
	}

	std::transform(result.begin(), result.end(), result.begin(), ::toupper);

	return result;
}

stdstring CStringEncrypt919::decrypt(stdstring input)
{
	unsigned int value;
	size_t index, offset;
	stdstring str, result = _T("");

	index = offset = 0;
	while (true)
	{
		str = input.substr(offset++ * 4, 4);
		if (0 == str.length())
			break;

		value = _tcstol(str.c_str(), NULL, 16) / m_key[index++];

		if (9 == index)
			index = 0;

		result += value;
	}

	return result;
}