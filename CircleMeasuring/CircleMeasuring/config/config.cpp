#include "stdafx.h"
#include "config.h"

#include "..\io\fileio.h"
#include "..\exception\exceptionplus.h"

CConfig::CConfig()
{
	m_length_per_pixel = 1.0;
	m_compensation = 0.0;

	m_auto_identification = 0;
	m_color_threshold = 80.0;
}

CConfig::~CConfig()
{
}

void CConfig::get_config(stdstring name)
{
	size_t size;
	CFileIO file;
	CIRCLE_CONFIG circle_config;
	stdstring config, value, temp;
	std::vector<stdstring> contents;

	try
	{
		file.read(name, contents);

		m_circles_config.clear();

		size = contents.size();
		for (size_t i = 0; i < size; i++)
		{
			config = trimstring(contents[i]);
			if (0 == config.length())
				continue;

			if (0 == config.find(_T("target length")))
			{
				splitstring(value, config, 1, '=');

				m_target_length = _tcstod(value.c_str(), NULL);
				continue;
			}

			if (0 == config.find(_T("length per pixel")))
			{
				splitstring(value, config, 1, '=');

				m_length_per_pixel = _tcstod(value.c_str(), NULL);
				continue;
			}

			if (0 == config.find(_T("compensation")))
			{
				splitstring(value, config, 1, '=');

				m_compensation = _tcstod(value.c_str(), NULL);
				continue;
			}

			if (0 == config.find(_T("auto identification")))
			{
				splitstring(value, config, 1, '=');

				m_auto_identification = _tstoi(value.c_str());

				continue;
			}

			if (0 == config.find(_T("black background")))
			{
				splitstring(value, config, 1, '=');

				m_black_background = _tstoi(value.c_str());

				continue;
			}

			if (0 == config.find(_T("color threshold")))
			{
				splitstring(value, config, 1, '=');

				m_color_threshold = _tcstod(value.c_str(), NULL);
				continue;
			}

			if (0 == config.find(_T("circle config")))
			{
				splitstring(temp, config, 1, '=');

				splitstring(value, temp, 0, ',');
				circle_config.standard = _tcstod(value.c_str(), NULL);

				splitstring(value, temp, 1, ',');
				circle_config.minimum = _tcstod(value.c_str(), NULL);

				splitstring(value, temp, 2, ',');
				circle_config.maximum = _tcstod(value.c_str(), NULL);

				splitstring(value, temp, 3, ',');
				circle_config.pixels_min = _tcstod(value.c_str(), NULL);

				splitstring(value, temp, 4, ',');
				circle_config.pixels_max = _tcstod(value.c_str(), NULL);

				m_circles_config.push_back(circle_config);

				continue;
			}
		}
	}
	catch (CExceptionPlus &e)
	{
		throw e;
	}
}

void CConfig::set_config(stdstring name)
{
	CFileIO file;
	TCHAR buffer[100];

	try
	{
		file.open(name, _T("w"));

		buffer[0] = 0;
		_stprintf_s(buffer, 100, _T("target length=%.15f\n"), m_target_length);
		file.write(buffer);

		buffer[0] = 0;
		_stprintf_s(buffer, 100, _T("length per pixel=%.15f\n"), m_length_per_pixel);
		file.write(buffer);

		buffer[0] = 0;
		_stprintf_s(buffer, 100, _T("compensation=%.15f\n"), m_compensation);
		file.write(buffer);

		buffer[0] = 0;
		_stprintf_s(buffer, 100, _T("auto identification=%d\n"), m_auto_identification);
		file.write(buffer);

		buffer[0] = 0;
		_stprintf_s(buffer, 100, _T("black background=%d\n"), m_black_background);
		file.write(buffer);

		buffer[0] = 0;
		_stprintf_s(buffer, 100, _T("color threshold=%.15f\n"), m_color_threshold);
		file.write(buffer);

		for (size_t i = 0; i < m_circles_config.size(); i++)
		{
			buffer[0] = 0;
			_stprintf_s(buffer, 100, _T("circle config=%.4f,%.4f,%.4f,%.4f,%.4f\n"), m_circles_config[i].standard, m_circles_config[i].minimum, m_circles_config[i].maximum, m_circles_config[i].pixels_min, m_circles_config[i].pixels_max);
			file.write(buffer);
		}
	}
	catch (CExceptionPlus &e)
	{
		throw e;
	}
}