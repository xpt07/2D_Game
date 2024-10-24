#include "Player.h"
#include "BackgroundTiles.h"
#include "Rect.h"
#include "vec2.h"

int main() {
	// Create a canvas window with dimensions 1024x768 and title “Tiles"
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Space Game");
	
	Player player("resources/L.png", vec2(512, 384));
	Rect rect(vec2(100, 100), vec2(200, 200));
	BackgroundTiles bg;

	//GamesEngineeringBase::Image bg;
	//bg.load("resources/background/Space_Background1.png");

	bool running = true; // Variable to control the main loop's running state.
	while (running)
	{
		// Check for input (key presses or window events)
		if (canvas.keyPressed(VK_ESCAPE))  
			break;
		// Clear the window for the next frame rendering
		canvas.clear();

		// Update game logic
		player.onUpdate(canvas);

		bg.draw(canvas);

		player.draw(canvas);

		// Display the frame on the screen. This must be called once the frame is finished in order to display the frame.
		canvas.present();
	}
	return 0;
}
