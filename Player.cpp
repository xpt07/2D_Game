#include "Player.h"

Player::Player() : Characters("resources/mainShip.png", vec2(0, 0)) {}

void Player::draw(Window& window) {
    // Draw player at a fixed position on the screen (e.g., the center)
    vec2 fixedScreenPosition(window.getWidth() / 2, window.getHeight() / 2);
    Characters::draw(window, fixedScreenPosition);
}
