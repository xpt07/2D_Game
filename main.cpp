#include "Player.h"
#include "Rect.h"
#include "vec2.h"
#include "Camera.h"
#include "Background.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

int main() {
	srand(static_cast<unsigned int>(time(nullptr)));

	// Create a canvas window with dimensions 1024x768 and title “Tiles"
	GamesEngineeringBase::Window canvas;
	canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Game");
	bool running = true; // Variable to control the main loop's running state.

	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
	Background background;
	Player player(vec2(WINDOW_WIDTH / 2, 2 * WINDOW_HEIGHT / 3));

	Timer tim;

	while (running)
	{
		// Check for input (key presses or window events)
		canvas.checkInput();

		// Clear the window for the next frame rendering
		canvas.clear();

		float dt = tim.dt();

		if (canvas.keyPressed(VK_ESCAPE)) break;

		// Update game logic
		player.onUpdate(canvas);

		camera.follow(player.getPos());
		background.draw(canvas, camera);
		player.draw(canvas);

		// Display the frame on the screen. This must be called once the frame is finished in order to display the frame.
		canvas.present();
	}
	return 0;
}
