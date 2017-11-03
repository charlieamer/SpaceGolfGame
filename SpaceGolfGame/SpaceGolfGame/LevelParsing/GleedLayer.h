#pragma once

#include "GleedBaseObject.h"
#include <vector>
#include <memory>

class GleedLayer : public GleedBaseObject
{
public:
	GleedLayer(const tinyxml2::XMLNode* node);
	~GleedLayer();
	std::vector<std::shared_ptr<GleedBaseObject>> objects;
};

