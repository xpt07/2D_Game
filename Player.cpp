#include "Player.h"


Player::Player(string sImage, vec2 startPos) : Characters(sImage, startPos)
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

bool Player::withinBounds(int x, int y, int width, int height)
{
    // Ensure player doesn't go outside the window's boundaries.
    int imageWidth = image.width;
    int imageHeight = image.height;

    return (x >= 0 && y >= 0 && x + imageWidth <= width && y + imageHeight <= height);
}
