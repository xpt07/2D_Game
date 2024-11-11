#include"core.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"
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
    std::vector<std::unique_ptr<PowerUp>> powerUps;
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
    background.load();

    Level level(1, WINDOW_WIDTH, 20, LevelType::FixedBoundary);
    int enemiesDefeated = 0;
    int enemiesToDefeatToAdvance = 10;

    Timer timer;
    float waveDelay = 1.0f;
    float waveTimer = 0.0f;
    float powerUpSpawnTimer = 0.0f;

    while (running) {
        canvas.checkInput();
        canvas.clear();

        if (canvas.keyPressed(VK_ESCAPE)) break;

        float deltaTime = timer.dt();
        waveTimer += deltaTime;
        powerUpSpawnTimer += deltaTime;

        if (waveTimer >= waveDelay) {
            waveTimer = 0.0f;
            level.spawnEnemies(enemies, player->getPosition());
        }

        // Spawn PowerUps every 15 seconds
        if (powerUpSpawnTimer >= 15.0f) {
            powerUpSpawnTimer = 0.0f;
            vec2 randomPos(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
            powerUps.push_back(std::make_unique<PowerUp>(randomPos));
        }

        background.draw(canvas, camera);

        player->onUpdate(canvas, deltaTime, background, camera);

        if (player->getHealth() <= 0) {
            std::cout << "Game Over! Player has been destroyed." << std::endl;
            break;  // End the game if the player is dead
        }

        player->shootAtNearestEnemy(enemies, projectiles);

        if (canvas.keyPressed('Q')) {
            player->useAOEAttack(enemies);
        }

        camera.follow(player->getPosition());
        player->draw(canvas, camera.getPosition());

        for (unsigned int i = 0; i < enemies.size(); ) {
            if (enemies[i]->getHealth() <= 0) {
                enemies.erase(enemies.begin() + i);  // Remove enemy if health is zero
            }
            else {
                enemies[i]->onUpdate(player->getPosition(), deltaTime);

                // Check if the enemy is a Bomber and should shoot at the player
                BomberEnemy* bomber = dynamic_cast<BomberEnemy*>(enemies[i].get());
                if (bomber) {
                    bomber->shootAtPlayer(player->getPosition(), projectiles);
                }

                enemies[i]->draw(canvas, camera.getPosition());
                ++i;  // Only increment if the enemy was not removed
            }
        }

        for (auto& projectile : projectiles) {
            projectile->onUpdate();
            projectile->draw(canvas, camera.getPosition());
        }

        // Draw and manage PowerUps
        for (auto& powerUp : powerUps) {
            powerUp->draw(canvas, camera.getPosition());
        }

        CollisionManager::checkCollisions(player.get(), enemies, projectiles, powerUps, camera, enemiesDefeated);


        // Check if it's time to switch to the infinite world level
        if (enemiesDefeated >= enemiesToDefeatToAdvance && level.getLevelType() == LevelType::FixedBoundary) {
            level.setLevelType(LevelType::InfiniteWorld);
            background.setInfiniteWorld(true);
            enemiesDefeated = 0;  // Reset the counter
            std::cout << "Level up! Switched to infinite world!" << std::endl;
        }

        canvas.present();
    }

    return 0;
}
