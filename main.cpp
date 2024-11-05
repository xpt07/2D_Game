#include "Player.h"
#include "Rect.h"
#include "vec2.h"
#include "Camera.h"
#include "Background.h"

constexpr int WINDOW_WIDTH = 1024;
constexpr int WINDOW_HEIGHT = 768;
constexpr float CAMERA_SPEED = 2.0f;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    GamesEngineeringBase::Window canvas;
    canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Game");
    bool running = true;

    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
    Background background;
    Player player;

    // Load the single tile for the infinite background
    background.load();

    Timer tim;

    while (running) {
        canvas.checkInput();
        canvas.clear();

        if (canvas.keyPressed(VK_ESCAPE)) break;

        // Calculate movement based on input
        vec2 movement(0, 0);
        if (canvas.keyPressed('W')) movement.y -= CAMERA_SPEED;
        if (canvas.keyPressed('S')) movement.y += CAMERA_SPEED;
        if (canvas.keyPressed('A')) movement.x -= CAMERA_SPEED;
        if (canvas.keyPressed('D')) movement.x += CAMERA_SPEED;

        // Move the camera based on player input
        camera.follow(camera.getPosition() + movement);

        // Draw the infinite background
        background.draw(canvas, camera);

        // Draw the player at the center of the screen
        player.draw(canvas);

        canvas.present();
    }
    return 0;
}
