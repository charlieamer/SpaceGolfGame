#pragma once

#include "GleedPosition.h"
#include <rapidxml.hpp>
#include <string>
#include <map>
#include "GleedColor.h"

class GleedBaseObject
{
public:
	GleedBaseObject(rapidxml::xml_node<>& node);
	~GleedBaseObject();
	GleedPosition position;
	std::string name;
	std::map<std::string, std::string> properties;
	std::map<std::string, GleedColor> colorProperties;
};

