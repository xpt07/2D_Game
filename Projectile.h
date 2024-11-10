#pragma once
#include "GameObject.h"

class Projectile : public GameObject {
public:
	Projectile(vec2 startPos, vec2 _direction, ObjectType _shooterType) :
		GameObject(startPos, ObjectType::Projectile), direction(_direction), speed(5.f), originType(_shooterType) {}

	void onUpdate() override {
		// Move the projectile in the specified direction
		pos.x += direction.x * speed;
		pos.y += direction.y * speed;
	}
	
	void draw(Window& canvas, const vec2& cameraOffset) {
        vec2 screenPos = pos - cameraOffset;

        hitbox = std::make_unique<Circle>(
            vec2(screenPos.x , screenPos.y),
            1
        );

        for (unsigned int i = 0; i < 5; i++) {
            for (unsigned int j = 0; j < 5; j++) {
                // Ensure the pixel is within the window bounds
                int drawX = static_cast<int>(screenPos.x + i);
                int drawY = static_cast<int>(screenPos.y + j);

                if (drawX >= 0 && drawX < static_cast<int>(canvas.getWidth()) &&
                    drawY >= 0 && drawY < static_cast<int>(canvas.getHeight())) {

                    canvas.draw(drawX, drawY, 255,0,0);
                    
                }
            }
        }
    }

	ObjectType getOriginType() const { return originType; }

private:
	vec2 direction;
	float speed;
	ObjectType originType;
};
