#pragma once

#include "GleedBaseObject.h"
#include <vector>
#include <memory>

class GleedLayer : public GleedBaseObject
{
public:
	GleedLayer(rapidxml::xml_node<> &node);
	~GleedLayer();
	std::vector<std::shared_ptr<GleedBaseObject>> objects;
};

