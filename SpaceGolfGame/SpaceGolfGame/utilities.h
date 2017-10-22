#pragma once
#include <entityx/Entity.h>
#include <vmath.h>
#include <math.h>
#include <rapidxml.hpp>
#include <string>
#include <memory>
#include <vector>
#include "LevelParsing/GleedBaseObject.h"
#include "LevelParsing/GleedRectangle.h"
#include "LevelParsing/GleedCircle.h"
#include "LevelParsing/GleedLayer.h"
#include "LevelParsing/GleedTexture.h"

namespace Utilities {
	bool isColliding(entityx::Entity &first, entityx::Entity &second);
	float getRadius(entityx::Entity &entity);
	Vector2f& getVelocity(entityx::Entity &entity);
	void solveQuadratic(float a, float b, float c, float &s1, float &s2);
	Vector2f getPointOfImpact(entityx::Entity &nonMoving, entityx::Entity &moving);
	float random(float from, float to);
	Vector2f randomVector(float from, float to);
	uint32_t abgr(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	uint32_t abgr(float r, float g, float b, float a);
    template<typename T>
    T clamp(T number, T mmin, T mmax) {
        return std::max(std::min(number, mmax), mmin);
    }

	template<typename T>
	T cap(T value, T from, T to);

	const std::vector<std::string> explode(const std::string& s, const char& c);
}
namespace Debug {
    enum PrintSeverity {
        PRINT_SILLY,
        PRINT_DEBUG,
        PRINT_INFO,
        PRINT_WARN,
        PRINT_ERROR
    };
    void p(PrintSeverity severity, const char* format, ...);
}

namespace FileUtilities {
	std::string readFile(std::string path);
}

namespace XmlUtilities {
	std::string value(rapidxml::xml_node<>& node);
	std::string value(rapidxml::xml_attribute<>& node);
	float parseFloat(rapidxml::xml_node<>& node);
	int parseInt(rapidxml::xml_node<>& node);
}

namespace GleedUtilities {
	template <typename T>
	T& getObjectByName(const std::vector<std::shared_ptr<T>> &objects, std::string name) 
    {
        for (unsigned i = 0; i < objects.size(); i++) {
            if (objects[i]->name == name) {
                return *objects[i];
            }
        }
        throw "Object with name " + name + " not found";
    };
	template GleedLayer& getObjectByName(const std::vector<std::shared_ptr<GleedLayer>> &objects, std::string name);
	template GleedCircle& getObjectByName(const std::vector<std::shared_ptr<GleedCircle>> &objects, std::string name);
	template GleedRectangle& getObjectByName(const std::vector<std::shared_ptr<GleedRectangle>> &objects, std::string name);

	Aabb3f rectangleToAABB(const GleedRectangle& rect);
	GleedRectangle& getRectangle(const GleedLayer& layer, std::string name);
	GleedCircle& getCircle(const GleedLayer& layer, std::string name);
	Aabb3f textureToAABB(const GleedTexture& texture);
}