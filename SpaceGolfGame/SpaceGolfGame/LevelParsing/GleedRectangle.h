#pragma once
#include "GleedBaseObject.h"
#include "GleedColor.h"

class GleedRectangle :
	public GleedBaseObject
{
public:
	GleedRectangle(rapidxml::xml_node<>& node);
	~GleedRectangle();
	float width, height;
	GleedColor color;
};

