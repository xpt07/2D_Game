#include"core.h"
#include "Player.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "Level.h"


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    GamesEngineeringBase::Window canvas;
    canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Game");
    bool running = true;

    Background background;
    auto player = std::make_unique<Player>();
    std::vector<std::unique_ptr<GameObject>> enemies;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);

    background.load();
    Level level(1, WINDOW_WIDTH, 20);

    Timer timer;
    float waveDelay = 1.0f;
    float waveTimer = 0.0f;

    while (running) {
        canvas.checkInput();
        canvas.clear();

        if (canvas.keyPressed(VK_ESCAPE)) break;

        // Update the timer
        float deltaTime = timer.dt();
        waveTimer += deltaTime;

        if (waveTimer >= waveDelay) {
            waveTimer = 0.0f;
            level.spawnEnemies(enemies, player->getPosition());
        }

        // Draw the background relative to the camera
        background.draw(canvas, camera);

        // Update and draw the player
        player->onUpdate(canvas, deltaTime);
        player->shootAtNearestEnemy(enemies, projectiles);
        // Move the camera to follow the player
        camera.follow(player->getPosition());
        player->draw(canvas, camera.getPosition());

        for (auto& enemy : enemies) {
            enemy->onUpdate(player->getPosition(), deltaTime);

            // If the enemy is a BomberEnemy, make it shoot at the player
            BomberEnemy* bomber = dynamic_cast<BomberEnemy*>(enemy.get());
            if (bomber) {
                bomber->shootAtPlayer(player->getPosition(), projectiles);
            }

            enemy->draw(canvas, camera.getPosition());
        }

        // Update and draw projectiles
        for (auto& projectile : projectiles) {
            projectile->onUpdate();
            projectile->draw(canvas, camera.getPosition());
        }

        CollisionManager::checkCollisions(player.get(), enemies, projectiles);

        canvas.present();
    }
    return 0;
}
