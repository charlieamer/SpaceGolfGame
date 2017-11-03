#pragma once
#include "GleedBaseObject.h"
#include "GleedColor.h"

class GleedRectangle :
	public GleedBaseObject
{
public:
	GleedRectangle(const tinyxml2::XMLNode* node);
	~GleedRectangle();
	float width, height;
	GleedColor color;
};

