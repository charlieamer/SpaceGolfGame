#include "GleedBaseObject.h"
#include "../utilities.h"

#include <iostream>

GleedBaseObject::GleedBaseObject(const tinyxml2::XMLNode* node) : position(node)
{
	name = XmlUtilities::value(node->FirstChildElement("Name"));
    std::cout << "Parsing " << name << std::endl;
	if (node->FirstChildElement("CustomProperties")) {
        std::cout << "Has custom properties" << std::endl;
		for (const tinyxml2::XMLElement* it = node->FirstChildElement("CustomProperties")->FirstChildElement("Property"); it; it = it->NextSiblingElement("Property")) {
			std::string propertyName = XmlUtilities::value(it->FindAttribute("Name"));
            std::cout << "Got " << propertyName << ":";
            if (it->FirstChildElement("string")) {
                std::string propertyValue = XmlUtilities::value(it->FirstChildElement("string"));
                std::cout << propertyValue;
                properties[propertyName] = propertyValue;
            } else if (it->FirstChildElement("Color")) {
                colorProperties[propertyName] = GleedColor(it->FirstChildElement("Color"));
            } else if (it->FirstChildElement("boolean")) {
                booleanProperties[propertyName] = strcmp(it->FirstChildElement("boolean")->ToElement()->GetText(), "true") == 0;
            } else {
                throw "Unknown property type";
            }
            std::cout << "\n";
		}
	}
}


GleedBaseObject::~GleedBaseObject()
{
}
