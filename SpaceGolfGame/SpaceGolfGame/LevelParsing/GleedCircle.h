#pragma once
#include "GleedBaseObject.h"
#include "GleedColor.h"
class GleedCircle :
	public GleedBaseObject
{
public:
	GleedCircle(rapidxml::xml_node<>& node);
	~GleedCircle();
	float radius;
	GleedColor color;
};

