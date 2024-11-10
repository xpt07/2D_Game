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

    Level level(1, WINDOW_WIDTH, 20, LevelType::FixedBoundary);
    int enemiesDefeated = 0;
    int enemiesToDefeatToAdvance = 10;

    Timer timer;
    float waveDelay = 1.0f;
    float waveTimer = 0.0f;

    while (running) {
        canvas.checkInput();
        canvas.clear();

        if (canvas.keyPressed(VK_ESCAPE)) break;

        float deltaTime = timer.dt();
        waveTimer += deltaTime;

        if (waveTimer >= waveDelay) {
            waveTimer = 0.0f;
            level.spawnEnemies(enemies, player->getPosition());
        }

        background.draw(canvas, camera);
        player->onUpdate(canvas, deltaTime, background, camera);
        player->shootAtNearestEnemy(enemies, projectiles);
        camera.follow(player->getPosition());
        player->draw(canvas, camera.getPosition());

        for (auto& enemy : enemies) {
            enemy->onUpdate(player->getPosition(), deltaTime);

            BomberEnemy* bomber = dynamic_cast<BomberEnemy*>(enemy.get());
            if (bomber) {
                bomber->shootAtPlayer(player->getPosition(), projectiles);
            }

            enemy->draw(canvas, camera.getPosition());
        }

        for (auto& projectile : projectiles) {
            projectile->onUpdate();
            projectile->draw(canvas, camera.getPosition());
        }

        CollisionManager::checkCollisions(player.get(), enemies, projectiles, camera, enemiesDefeated);


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
