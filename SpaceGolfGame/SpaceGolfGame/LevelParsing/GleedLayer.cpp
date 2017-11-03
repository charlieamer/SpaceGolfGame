#include "GleedLayer.h"

#include "GleedCircle.h"
#include "GleedRectangle.h"
#include "GleedTexture.h"

GleedLayer::GleedLayer(const tinyxml2::XMLNode *node) :
	GleedBaseObject(node->FirstChildElement("LayerProperties"))
{
	for (const tinyxml2::XMLNode* it = node->FirstChildElement("Editors")->FirstChildElement("Editor"); it; it = it->NextSiblingElement("Editor")) {
		if (it->FirstChildElement("CircleItemProperties")) {
			objects.emplace_back(new GleedCircle(it->FirstChildElement("CircleItemProperties")));
		} else if (it->FirstChildElement("RectangleItemProperties")) {
			objects.emplace_back(new GleedRectangle(it->FirstChildElement("RectangleItemProperties")));
		}
		else if (it->FirstChildElement("TextureItemProperties")) {
			objects.emplace_back(new GleedTexture(it->FirstChildElement("TextureItemProperties")));
		}
		else {
			throw "Invalid object in layer";
		}
	}
}

GleedLayer::~GleedLayer()
{
}
