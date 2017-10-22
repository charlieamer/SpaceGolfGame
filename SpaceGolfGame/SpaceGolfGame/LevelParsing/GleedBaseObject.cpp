#include "GleedBaseObject.h"
#include "../utilities.h"


GleedBaseObject::GleedBaseObject(rapidxml::xml_node<>& node) : position(node)
{
	name = XmlUtilities::value(*node.first_node("Name"));
	if (node.first_node("CustomProperties")) {
		for (rapidxml::xml_node<>* it = node.first_node("CustomProperties")->first_node("Property"); it; it = it->next_sibling("Property")) {
			std::string propertyName = XmlUtilities::value(*it->first_attribute("Name"));
            if (it->first_node("string")) {
                std::string propertyValue = XmlUtilities::value(*it->first_node("string"));
                properties[propertyName] = propertyValue;
            } else if (it->first_node("Color")) {
                colorProperties[propertyName] = GleedColor(*it->first_node("Color"));
            } else if (it->first_node("boolean")) {
                booleanProperties[propertyName] = strcmp(it->first_node("boolean")->value(), "true") == 0;
            } else {
                throw "Unknown property type";
            }
		}
	}
}


GleedBaseObject::~GleedBaseObject()
{
}
