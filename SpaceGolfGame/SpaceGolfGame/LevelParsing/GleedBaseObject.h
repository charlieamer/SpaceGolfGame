#pragma once

#include "GleedPosition.h"
#include <tinyxml2.h>
#include <string>
#include <map>
#include "GleedColor.h"

class GleedBaseObject
{
public:
	GleedBaseObject(const tinyxml2::XMLNode *node);
	~GleedBaseObject();
	GleedPosition position;
	std::string name;
	std::map<std::string, std::string> properties;
	std::map<std::string, GleedColor> colorProperties;
    std::map<std::string, bool> booleanProperties;
};

