#pragma once

#include <tinyxml2.h>

class GleedPosition
{
public:
	GleedPosition(const tinyxml2::XMLNode* node);
	~GleedPosition();
	float x, y;
};

