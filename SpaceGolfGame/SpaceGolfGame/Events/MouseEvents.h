#pragma once

#include <vmath.h>
struct MouseMoveEvent {
	MouseMoveEvent(const Vector2i &delta, const Vector2i &now) : delta(delta), now(now) {}
	Vector2i delta;
	Vector2i now;
};

struct LeftMouseDownEvent {

};

struct LeftMouseUpEvent {

};