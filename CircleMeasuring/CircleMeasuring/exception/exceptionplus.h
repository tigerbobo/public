#pragma once

#include <vector>
#include <iostream>

#include "..\stdstring\stdstring.h"

/************************************************************************
try
{
}
catch (CExceptionPlus &e)
{
for (size_t i = 0; i < e.get_exception().size(); i++)
MessageBox((e.get_exception()[i].category + _T(" : ") + e.get_exception()[i].name + _T(" : ") + e.get_exception()[i].result).c_str(), _T("example"), MB_OK | MB_ICONERROR);
}
************************************************************************/

typedef struct _EXCEPTION_INFO
{
	stdstring category;
	stdstring name;
	stdstring result;

	stdstring file;
	stdstring function;
	stdstring line;
}EXCEPTION_INFO;

class CExceptionPlus
{
public:
	CExceptionPlus(void)
	{
		m_exceptions.reserve(10);
	};
	virtual ~CExceptionPlus(void)
	{

	};
private:
	std::vector<EXCEPTION_INFO> m_exceptions;
public:
	void add_exception(stdstring strCategory, stdstring strName, stdstring strResult, stdstring strFile, stdstring strFunc, int nLine)
	{
		EXCEPTION_INFO info;

		info.category = strCategory;
		info.name = strName;
		info.result = strResult;

		info.file = strFile;
		info.function = strFunc;

		stdstringstream stream;
		stream << nLine;
		info.line = stream.str();

		m_exceptions.insert(m_exceptions.begin(), info);
	};

	std::vector<EXCEPTION_INFO> get_exception(void)
	{
		return m_exceptions;
	};
public:
	void show_exception(stdstring caption)
	{
		for (unsigned int i = 0; i < m_exceptions.size(); i++)
		{
			stdcout << caption.c_str() << std::endl;
			stdcout << (m_exceptions[i].category + _T(" : ") + m_exceptions[i].name + _T(" : ") + m_exceptions[i].result).c_str() << std::endl;
		}
	}
};

#ifdef UNICODE
#define EXCEPTION(category, name, result)												\
	CExceptionPlus e;																	\
	e.add_exception(category, name, result, __FILEW__, __FUNCTIONW__, __LINE__);		\
	throw e;

#define EXCEPTIONEX(category, name, result)												\
	{																					\
		CExceptionPlus e;																\
		e.add_exception(category, name, result, __FILEW__, __FUNCTIONW__, __LINE__);	\
		throw e;																		\
	}

#define THROW_EXCEPTION(e, category, name, result)										\
	e.add_exception(category, name, result, __FILEW__, __FUNCTIONW__, __LINE__);		\
	throw;
#else
#define EXCEPTION(category, name, result)												\
	CExceptionPlus e;																	\
	e.add_exception(category, name, result, __FILE__, __FUNCTION__, __LINE__);			\
	throw e;

#define EXCEPTIONEX(category, name, result)												\
	{																					\
		CExceptionPlus e;																\
		e.add_exception(category, name, result, __FILE__, __FUNCTION__, __LINE__);		\
		throw e;																		\
	}

#define THROW_EXCEPTION(e, category, name, result)										\
	e.add_exception(category, name, result, __FILE__, __FUNCTION__, __LINE__);			\
	throw;
#endif