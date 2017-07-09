#pragma once
#include "GleedBaseObject.h"
#include "GleedColor.h"
#include <string>
class GleedTexture :
	public GleedBaseObject
{
public:
	GleedTexture(rapidxml::xml_node<> &node);
	~GleedTexture();

	GleedColor tint;
	float scaleX, scaleY;
	float originX, originY;
	std::string path;

};

