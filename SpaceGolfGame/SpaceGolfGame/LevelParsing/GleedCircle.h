#pragma once
#include "GleedBaseObject.h"
#include "GleedColor.h"
class GleedCircle :
	public GleedBaseObject
{
public:
	GleedCircle(const tinyxml2::XMLNode* node);
	~GleedCircle();
	float radius;
	GleedColor color;
};

