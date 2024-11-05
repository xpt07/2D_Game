#include "Player.h"


Player::Player(vec2 startPos) : Characters("resources/mainShip.png", startPos)
{
}

void Player::onUpdate(GamesEngineeringBase::Window& window)
{
    unsigned int windowWidth = window.getWidth();
    unsigned int windowHeight = window.getHeight();
    int moveSpeed = 2;

    if (window.keyPressed('W')) pos.y -= moveSpeed;
    if (window.keyPressed('S')) pos.y += moveSpeed;
    if (window.keyPressed('A')) pos.x -= moveSpeed;
    if (window.keyPressed('D')) pos.x += moveSpeed;
}
