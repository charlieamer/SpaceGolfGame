#include "GleedBaseObject.h"
#include "../utilities.h"


GleedBaseObject::GleedBaseObject(rapidxml::xml_node<>& node) : position(node)
{
	name = XmlUtilities::value(*node.first_node("Name"));
	if (node.first_node("CustomProperties")) {
		for (rapidxml::xml_node<>* it = node.first_node("CustomProperties")->first_node("Property"); it; it = it->next_sibling("Property")) {
			std::string propertyName = XmlUtilities::value(*it->first_attribute("Name"));
			std::string propertyValue = XmlUtilities::value(*it->first_node("string"));
			properties[propertyName] = propertyValue;
		}
	}
}


GleedBaseObject::~GleedBaseObject()
{
}
