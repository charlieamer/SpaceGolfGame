#include "GleedLevel.h"

GleedLevel::GleedLevel(rapidxml::xml_node<>& node) : GleedBaseObject(*node.first_node("LevelProperties"))
{
	for (auto it = node.first_node("Layers")->first_node("Layer"); it; it = it->next_sibling("Layer")) {
		layers.emplace_back(new GleedLayer(*it));
	}
}

GleedLevel::~GleedLevel()
{
}
