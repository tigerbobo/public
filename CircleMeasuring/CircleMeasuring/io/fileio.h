#pragma once

#include <vector>

#include "..\stdstring\stdstring.h"

class CFileIO
{
public:
	CFileIO();
	~CFileIO();
private:
	FILE *m_file;

	stdstring m_name;
public:
	void open(stdstring name, stdstring mode);

	void read(stdstring &result);
	void read(stdstring name, std::vector<stdstring> &contents);

	void write(stdstring string);
	void write(stdstring name, stdstring string);
};