#include "GleedCircle.h"
#include "../utilities.h"

GleedCircle::GleedCircle(rapidxml::xml_node<>& node) : GleedBaseObject(node), color(*node.first_node("FillColor"))
{
	radius = XmlUtilities::parseFloat(*node.first_node("Radius"));
}

GleedCircle::~GleedCircle()
{
}
