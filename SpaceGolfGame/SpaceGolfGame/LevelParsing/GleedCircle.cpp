#include "GleedCircle.h"
#include "../utilities.h"

GleedCircle::GleedCircle(const tinyxml2::XMLNode* node) : GleedBaseObject(node), color(node->FirstChildElement("FillColor"))
{
	radius = XmlUtilities::parseFloat(node->FirstChildElement("Radius"));
}

GleedCircle::~GleedCircle()
{
}
