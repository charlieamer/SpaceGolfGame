#pragma once

#include <vector>
#include <memory>
#include "GleedLayer.h"

class GleedLevel : public GleedBaseObject
{
public:
	GleedLevel(const tinyxml2::XMLNode *node);
	~GleedLevel();
	std::vector<std::shared_ptr<GleedLayer>> layers;
};

