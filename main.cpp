#include "Player.h"
#include "Rect.h"
#include "vec2.h"
#include "Camera.h"
#include "Background.h"

int main() {
	srand(static_cast<unsigned int>(time(nullptr)));
	// Create a canvas window with dimensions 1024x768 and title “Tiles"
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Space Game");
	bool running = true; // Variable to control the main loop's running state.

	Background background;
	Player player("resources/L.png", vec2((canvas.getWidth() / 2), 2 * canvas.getHeight() / 3));


	Timer tim;
	int y = 0;

	while (running)
	{
		// Check for input (key presses or window events)
		canvas.checkInput();

		// Clear the window for the next frame rendering
		canvas.clear();

		float dt = tim.dt();
		int move = static_cast<int>((500.f * dt));



		int x = 0;
		if (canvas.keyPressed(VK_ESCAPE)) break;
		if (canvas.keyPressed('W')) y += 5;
		if (canvas.keyPressed('S')) y -= 1;
		if (canvas.keyPressed('A')) x -= move;
		if (canvas.keyPressed('D')) x += move;


		// Update game logic
		player.onUpdate(canvas);

		background.draw(canvas, y);
		player.draw(canvas);

		// Display the frame on the screen. This must be called once the frame is finished in order to display the frame.
		canvas.present();
	}
	return 0;
}
