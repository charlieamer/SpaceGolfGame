#include "GleedRectangle.h"

#include "../utilities.h"

GleedRectangle::GleedRectangle(const tinyxml2::XMLNode* node) : GleedBaseObject(node), color(node->FirstChildElement("FillColor"))
{
	width = XmlUtilities::parseFloat(node->FirstChildElement("Width"));
	height = XmlUtilities::parseFloat(node->FirstChildElement("Height"));
}


GleedRectangle::~GleedRectangle()
{
}
