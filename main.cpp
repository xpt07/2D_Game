#include "Player.h"
#include "vec2.h"

int main() {
	// Create a canvas window with dimensions 1024x768 and title “Tiles"
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Tiles");
	
	Player player("resources/L.png", vec2(512, 384));

	GamesEngineeringBase::Image bg;
	bg.load("resources/background/Space_Background1.png");

	bool running = true; // Variable to control the main loop's running state.
	while (running)
	{
		// Check for input (key presses or window events)
		if (canvas.keyPressed(VK_ESCAPE))  break;
		// Clear the window for the next frame rendering
		canvas.clear();

		// Update game logic
		player.onUpdate(canvas);


		for (unsigned int i = 0; i < bg.width; i++)
			for (unsigned int j = 0; j < bg.height; j++)
				if (bg.alphaAt(i, j) > 0)
					canvas.draw(i, j, bg.atUnchecked(i,j));

		player.draw(canvas);

		// Display the frame on the screen. This must be called once the frame is finished in order to display the frame.
		canvas.present();
	}
	return 0;
}
