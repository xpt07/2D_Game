#include"core.h"
#include "Player.h"
#include "Enemy.h"


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    GamesEngineeringBase::Window canvas;
    canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Game");
    bool running = true;

    Background background;
    Enemy* kamikaze = new Enemy("resources/kamikaze_plane_sprite.png", vec2(200, 100), EnemyType::Kamikaze);
    Player* player = new Player();
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);

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

        // Update player position
        player->pos += movement;

        // Move the camera to follow the player
        camera.follow(player->getPosition());

        // Draw the background relative to the camera
        background.draw(canvas, camera);

        // Update and draw the player
        player->onUpdate();
        player->draw(canvas, camera.getPosition());

        // Update and draw the enemy
        kamikaze->onUpdate(player->getPosition());
        kamikaze->draw(canvas, camera.getPosition());

        canvas.present();
    }
    return 0;
}
