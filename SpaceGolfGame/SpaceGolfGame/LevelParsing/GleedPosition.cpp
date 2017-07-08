#include "GleedPosition.h"
#include "../utilities.h"

GleedPosition::GleedPosition(rapidxml::xml_node<> &node)
{
	x = XmlUtilities::parseFloat(*node.first_node("Position")->first_node("X"));
	y = XmlUtilities::parseFloat(*node.first_node("Position")->first_node("Y"));
}

GleedPosition::~GleedPosition()
{
}
