#include "Player.h"


Player::Player(string sImage, unsigned int startX, unsigned int startY) : Characters(sImage, startX, startY)
{

}

void Player::onUpdate()
{
	if (window.keyPressed('W')) y -= 2;
	if (window.keyPressed('S')) y += 2;
	if (window.keyPressed('A')) x -= 2;
	if (window.keyPressed('D')) x += 2;
}
