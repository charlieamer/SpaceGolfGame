#pragma once

#include <rapidxml.hpp>

class GleedPosition
{
public:
	GleedPosition(rapidxml::xml_node<> &node);
	~GleedPosition();
	float x, y;
};

