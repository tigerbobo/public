#include "stdafx.h"
#include "FileIO.h"

#include <memory>

#include "..\strings\strings.h"
#include "..\exception\ExceptionPlus.h"

#define _MAX_LENGTH			2048

CFileIO::CFileIO()
{
	m_file = NULL;

	_tsetlocale(LC_ALL, _T(""));
}

CFileIO::~CFileIO()
{
	if (m_file)
	{
		fclose(m_file);
		m_file = NULL;
	}
}

void CFileIO::open(stdstring name, stdstring mode)
{
	int result;

	if (m_file)
	{
		result = fclose(m_file);
		if (result)
			EXCEPTIONEX(IDS_FILE, IDS_FILE_CLOSE, m_name);

		m_file = NULL;
		m_name = _T("");
	}

	result = _tfopen_s(&m_file, name.c_str(), mode.c_str());
	if (result)
		EXCEPTIONEX(IDS_FILE, IDS_FILE_OPEN, name);

	m_name = name;
}

void CFileIO::read(stdstring &string)
{
	TCHAR buffer[_MAX_LENGTH + 1] = { 0 };

	if (NULL == _fgetts(buffer, _MAX_LENGTH, m_file))
		EXCEPTIONEX(IDS_FILE, IDS_FILE_READ, m_name);

	string = buffer;
}

void CFileIO::read(stdstring name, std::vector<stdstring> &contents)
{
	FILE *file;
	int result;
	std::shared_ptr<FILE> ptr;
	TCHAR buffer[_MAX_LENGTH + 1] = { 0 };

	result = _tfopen_s(&file, name.c_str(), _T("r"));
	if (result)
		EXCEPTIONEX(IDS_FILE, IDS_FILE_OPEN, name);

	ptr.reset(file, fclose);

	contents.clear();
	while (!feof(file))
	{
		if (NULL == _fgetts(buffer, _MAX_LENGTH, file))
		{
			if (ferror(file))
				EXCEPTIONEX(IDS_FILE, IDS_FILE_READ, name)
			else
				break;
		}
		else
			contents.push_back(buffer);
	}
}

void CFileIO::write(stdstring string)
{
	int result;

	result = _fputts(string.c_str(), m_file);
	if (result)
		EXCEPTIONEX(IDS_FILE, IDS_FILE_WRITE, m_name);
}

void CFileIO::write(stdstring name, stdstring string)
{
	FILE *file;
	int result;
	std::shared_ptr<FILE> ptr;

	result = _tfopen_s(&file, name.c_str(), _T("a"));
	if (result)
		EXCEPTIONEX(IDS_FILE, IDS_FILE_OPEN, name);

	ptr.reset(file, fclose);

	result = _fputts(string.c_str(), file);
	if (result)
		EXCEPTIONEX(IDS_FILE, IDS_FILE_WRITE, name);
}