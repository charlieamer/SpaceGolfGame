#pragma once
#include <entityx/Entity.h>
#include <vmath.h>
#include <math.h>

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
	T cap(T value, T from, T to);
}