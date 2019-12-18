#pragma once

#include <vector>

#include "..\stdstring\stdstring.h"

typedef struct
{
	double standard;		//standard circle diameter
	double minimum;			//minimum circle diameter
	double maximum;			//minimum circle diameter

	double pixels_min;		//pixels of contour(min)
	double pixels_max;		//pixels of contour(max)
}CIRCLE_CONFIG;

class CConfig
{
public:
	CConfig();
	~CConfig();
public:
	double m_target_length;
	double m_length_per_pixel;
	double m_compensation;

	int m_auto_identification;
	int m_black_background;
	double m_color_threshold;

	std::vector<CIRCLE_CONFIG> m_circles_config;
public:
	void get_config(stdstring name);
	void set_config(stdstring name);
};

