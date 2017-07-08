#pragma once

#include <rapidxml.hpp>

class GleedColor
{
public:
	GleedColor(rapidxml::xml_node<>& node);
	~GleedColor();
	unsigned char r, g, b, a;
};

