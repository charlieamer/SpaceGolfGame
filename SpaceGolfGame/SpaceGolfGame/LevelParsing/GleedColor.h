#pragma once

#include <tinyxml2.h>

class GleedColor
{
public:
	GleedColor(const tinyxml2::XMLNode* node);
    GleedColor(){}
	unsigned char r, g, b, a;
};

