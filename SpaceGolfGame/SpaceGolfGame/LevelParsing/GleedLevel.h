#pragma once

#include <vector>
#include <memory>
#include "GleedLayer.h"

class GleedLevel : public GleedBaseObject
{
public:
	GleedLevel(rapidxml::xml_node<>& node);
	~GleedLevel();
	std::vector<std::shared_ptr<GleedLayer>> layers;
};

