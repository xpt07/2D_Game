#include <iostream>
#include "GamesEngineeringBase.h"

using namespace std;

int main() {
	// Create a canvas window with dimensions 1024x768 and title “Tiles"
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Tiles");
	
	GamesEngineeringBase::Image L;
	L.load("resources/L.png");
	unsigned int planeX = canvas.getWidth() / 2 - (L.width / 2);
	unsigned int planeY = canvas.getHeight() / 2 - (L.height / 2);

	bool running = true; // Variable to control the main loop's running state.
	while (running)
	{
		// Check for input (key presses or window events)
		// Clear the window for the next frame rendering
		canvas.clear();
		// Update game logic
		if (canvas.keyPressed(VK_ESCAPE))  break;
		if (canvas.keyPressed('W')) planeY -= 2;
		if (canvas.keyPressed('S')) planeY += 2;
		if (canvas.keyPressed('A')) planeX -= 2;
		if (canvas.keyPressed('D')) planeX += 2;


		for (unsigned int i = 0; i < canvas.getWidth(); i++)
			for (unsigned int j = 0; j < canvas.getHeight(); j++)
			{
				canvas.draw(i, j, 0, 0, 255);
			}

		for (unsigned int i = 0; i < L.width; i++)
			for (unsigned int j = 0; j < L.height; j++)
			{
				if(L.alphaAt(i,j)> 200)
					canvas.draw(planeX + i, planeY + j, L.at(i, j));
			}

		// Display the frame on the screen. This must be called once the frame is finished in order to display the frame.
		canvas.present();
	}
	return 0;
}
