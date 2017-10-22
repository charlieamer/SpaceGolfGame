#include "GleedColor.h"
#include "../utilities.h"
#include <string>

GleedColor::GleedColor(rapidxml::xml_node<>& node)
{
	r = XmlUtilities::parseInt(*node.first_node("R"));
	g = XmlUtilities::parseInt(*node.first_node("G"));
	b = XmlUtilities::parseInt(*node.first_node("B"));
	a = XmlUtilities::parseInt(*node.first_node("A"));
}
