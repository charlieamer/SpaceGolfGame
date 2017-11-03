#include "GleedColor.h"
#include "../utilities.h"
#include <string>

GleedColor::GleedColor(const tinyxml2::XMLNode* node)
{
	r = XmlUtilities::parseInt(node->FirstChildElement("R"));
	g = XmlUtilities::parseInt(node->FirstChildElement("G"));
	b = XmlUtilities::parseInt(node->FirstChildElement("B"));
	a = XmlUtilities::parseInt(node->FirstChildElement("A"));
}
