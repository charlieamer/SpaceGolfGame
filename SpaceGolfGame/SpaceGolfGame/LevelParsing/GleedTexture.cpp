#include "GleedTexture.h"

#include "../utilities.h"

GleedTexture::GleedTexture(const tinyxml2::XMLNode* node) : GleedBaseObject(node), tint(node->FirstChildElement("TintColor"))
{
	auto scale = node->FirstChildElement("Scale");
	scaleX = XmlUtilities::parseFloat(scale->FirstChildElement("X"));
	scaleY = XmlUtilities::parseFloat(scale->FirstChildElement("Y"));

	auto origin = node->FirstChildElement("Origin");
	originX = XmlUtilities::parseFloat(origin->FirstChildElement("X"));
	originY = XmlUtilities::parseFloat(origin->FirstChildElement("Y"));

	path = XmlUtilities::value(node->FirstChildElement("TexturePathRelativeToContentRoot"));
}


GleedTexture::~GleedTexture()
{
}
