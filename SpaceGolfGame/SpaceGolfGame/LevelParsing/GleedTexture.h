#pragma once
#include "GleedBaseObject.h"
#include "GleedColor.h"
#include <string>
class GleedTexture :
	public GleedBaseObject
{
public:
	GleedTexture(const tinyxml2::XMLNode* node);
	~GleedTexture();

	GleedColor tint;
	float scaleX, scaleY;
	float originX, originY;
	std::string path;

};

