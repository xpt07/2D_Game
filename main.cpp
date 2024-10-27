#include "Player.h"
#include "Rect.h"
#include "vec2.h"
#include "Camera.h"
#include "Background.h"

int main() {
	// Create a canvas window with dimensions 1024x768 and title “Tiles"
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Space Game");

	Background background;
	Camera camera;
	Player player("resources/L.png", vec2(512, 384));

	bool running = true; // Variable to control the main loop's running state.
	while (running)
	{
		// Check for input (key presses or window events)
		if (canvas.keyPressed(VK_ESCAPE))  
			break;

		// Move the camera based on input (for example, arrow keys)
		if (canvas.keyPressed(VK_RIGHT)) camera.move(5, 0);
		if (canvas.keyPressed(VK_LEFT)) camera.move(-5, 0);
		if (canvas.keyPressed(VK_DOWN)) camera.move(0, 5);
		if (canvas.keyPressed(VK_UP)) camera.move(0, -5);

		// Clear the window for the next frame rendering
		canvas.clear();

		background.draw(canvas, camera);

		// Update game logic
		player.onUpdate(canvas);

		player.draw(canvas);

		// Display the frame on the screen. This must be called once the frame is finished in order to display the frame.
		canvas.present();
	}
	return 0;
}
