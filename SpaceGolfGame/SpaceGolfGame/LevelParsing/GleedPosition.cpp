#include "GleedPosition.h"
#include "../utilities.h"

GleedPosition::GleedPosition(const tinyxml2::XMLNode* node)
{
	x = XmlUtilities::parseFloat(node->FirstChildElement("Position")->FirstChildElement("X"));
	y = XmlUtilities::parseFloat(node->FirstChildElement("Position")->FirstChildElement("Y"));
}

GleedPosition::~GleedPosition()
{
}
