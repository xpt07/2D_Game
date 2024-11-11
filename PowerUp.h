#pragma once
#include "GameObject.h"

class PowerUp : public GameObject {
public:
	PowerUp(vec2 startPos);
	void draw(Window& window, const vec2& cameraOffset);
	bool isCollected() const { return collected; }

private:
	bool collected;
};