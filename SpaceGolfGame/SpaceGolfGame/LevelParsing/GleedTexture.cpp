#include "GleedTexture.h"

#include "../utilities.h"

GleedTexture::GleedTexture(rapidxml::xml_node<> &node) : GleedBaseObject(node), tint(*node.first_node("TintColor"))
{
	auto scale = node.first_node("Scale");
	scaleX = XmlUtilities::parseFloat(*scale->first_node("X"));
	scaleY = XmlUtilities::parseFloat(*scale->first_node("Y"));

	auto origin = node.first_node("Origin");
	originX = XmlUtilities::parseFloat(*origin->first_node("X"));
	originY = XmlUtilities::parseFloat(*origin->first_node("Y"));

	path = XmlUtilities::value(*node.first_node("TexturePathRelativeToContentRoot"));
}


GleedTexture::~GleedTexture()
{
}
