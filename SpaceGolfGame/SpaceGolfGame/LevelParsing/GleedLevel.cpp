#include "GleedLevel.h"

GleedLevel::GleedLevel(const tinyxml2::XMLNode *node) : GleedBaseObject(node->FirstChildElement("LevelProperties"))
{
	for (auto it = node->FirstChildElement("Layers")->FirstChildElement("Layer"); it; it = it->NextSiblingElement("Layer")) {
		layers.emplace_back(new GleedLayer(it));
	}
}

GleedLevel::~GleedLevel()
{
}
