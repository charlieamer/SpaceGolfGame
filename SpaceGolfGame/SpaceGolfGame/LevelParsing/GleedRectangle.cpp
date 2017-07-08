#include "GleedRectangle.h"

#include "../utilities.h"

GleedRectangle::GleedRectangle(rapidxml::xml_node<>& node) : GleedBaseObject(node), color(*node.first_node("FillColor"))
{
	width = XmlUtilities::parseFloat(*node.first_node("Width"));
	height = XmlUtilities::parseFloat(*node.first_node("Height"));
}


GleedRectangle::~GleedRectangle()
{
}
