#include "GleedLayer.h"

#include "GleedCircle.h"
#include "GleedRectangle.h"

GleedLayer::GleedLayer(rapidxml::xml_node<>& node) :
	GleedBaseObject(*node.first_node("LayerProperties"))
{
	for (rapidxml::xml_node<>* it = node.first_node("Editors")->first_node("Editor"); it; it = it->next_sibling("Editor")) {
		if (it->first_node("CircleItemProperties")) {
			objects.emplace_back(new GleedCircle(*it->first_node("CircleItemProperties")));
		} else if (it->first_node("RectangleItemProperties")) {
			objects.emplace_back(new GleedRectangle(*it->first_node("RectangleItemProperties")));
		}
		else {
			throw "Invalid object in layer";
		}
	}
}

GleedLayer::~GleedLayer()
{
}
