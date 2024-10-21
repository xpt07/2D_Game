#include <iostream>
#include "GamesEngineeringBase.h"
#include "Player.h"

using namespace std;

int main() {
	// Create a canvas window with dimensions 1024x768 and title “Tiles"
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Tiles");
	
	Player player("resources/L.png", 512, 384);

	bool running = true; // Variable to control the main loop's running state.
	while (running)
	{
		// Check for input (key presses or window events)
		// Clear the window for the next frame rendering
		canvas.clear();

		// Update game logic
		if (canvas.keyPressed(VK_ESCAPE))  break;
		player.onUpdate();


		for (unsigned int i = 0; i < canvas.getWidth(); i++)
			for (unsigned int j = 0; j < canvas.getHeight(); j++)
			{
				canvas.draw(i, j, 0, 0, 255);
			}

		player.draw(canvas);

		// Display the frame on the screen. This must be called once the frame is finished in order to display the frame.
		canvas.present();
	}
	return 0;
}
