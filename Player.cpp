#include "Player.h"


Player::Player(string sImage) : Characters(sImage)
{

}

void Player::onUpdate()
{
	if (window.keyPressed('W')) planeY -= 2;
	if (window.keyPressed('S')) planeY += 2;
	if (window.keyPressed('A')) planeX -= 2;
	if (window.keyPressed('D')) planeX += 2;
}
