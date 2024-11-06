#pragma once
#include "Shape.h"

class Rect : public Shape
{
public:
	Rect(vec2 _s, vec2 _e) :
		s(_s), e(_e)
	{}

	void setPosition(vec2 newStart, vec2 newEnd) {
		s = newStart;
		e = newEnd;
	}

	bool inside(vec2 p) override {
		if (p.x <= e.x && p.x >= s.x)
			if (p.y <= e.y && p.y >= s.y)
				return true;

		return false;
	}

	float area() override {
		return ((e.x - s.x) * (e.y - s.y));
	}

	void draw(Window& window) override {
		for (int i = s.x; i <= e.x; i++) {
			for (int j = s.y; j <= e.y; j++) {
				window.draw(i, j, 255, 255, 255); // White color
			}
		}
	}

private:
	vec2 s, e;
};
