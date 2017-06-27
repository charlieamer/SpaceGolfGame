#pragma once

#include <vmath.h>
struct MouseMoveEvent {
	MouseMoveEvent(const Vector2i &delta, const Vector2i &now) : delta(delta), now(now) {}
	Vector2i delta;
	Vector2i now;
};

struct LeftMouseDownEvent {
	LeftMouseDownEvent(const Vector2i mouse) : position(mouse) {}
	Vector2i position;
};

struct LeftMouseUpEvent {
	LeftMouseUpEvent(const Vector2i mouse) : position(mouse) {}
	Vector2i position;
};