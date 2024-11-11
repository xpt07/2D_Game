#include "core.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "CollisionManager.h"
#include "Level.h"
#include <iostream>
#include <fstream>

// Function to save the game state to a file
void saveGame(const Player* player, GameObject* enemies[], int enemyCount, int score, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file to save game state: " << filename << std::endl;
        return;
    }

    // Save player position and health
    file << player->getPosition().x << " " << player->getPosition().y << " " << player->getHealth() << "\n";

    // Save enemies' positions, health, and type
    for (int i = 0; i < enemyCount; ++i) {
        int enemyType = static_cast<int>(enemies[i]->getCharacterType());
        file << enemyType << " " << enemies[i]->getPosition().x << " " << enemies[i]->getPosition().y << " " << enemies[i]->getHealth() << "\n";
    }

    // Save score
    file << score << "\n";

    file.close();
}

// Function to load the game state from a file
void loadGame(Player* player, GameObject* enemies[], int& enemyCount, int& score, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file to load game state: " << filename << std::endl;
        return;
    }

    // Load player position and health
    float x, y;
    int health;
    file >> x >> y >> health;
    player->setPosition(vec2(x, y));
    player->setHealth(health);

    // Ensure player-specific properties are reset
    player->resetMovement();

    // Load enemies' positions, health, and type
    enemyCount = 0;
    int enemyType;
    while (file >> enemyType >> x >> y >> health) {
        if (enemyCount >= MAX_ENEMIES) break;
        switch (static_cast<ObjectType>(enemyType)) {
        case ObjectType::Kamikaze:
            enemies[enemyCount++] = new KamikazeEnemy(vec2(x, y));
            break;
        case ObjectType::Bomber:
            enemies[enemyCount++] = new BomberEnemy(vec2(x, y), health);
            break;
        case ObjectType::Destroyer:
            enemies[enemyCount++] = new DestroyerEnemy(vec2(x, y));
            break;
        case ObjectType::Sniper:
            enemies[enemyCount++] = new SniperEnemy(vec2(x, y));
            break;
        default:
            std::cerr << "Warning: Unknown enemy type loaded from file." << std::endl;
            break;
        }
    }

    // Load score
    file >> score;

    file.close();
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    GamesEngineeringBase::Window canvas;
    canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Game");

    bool running = true;
    Background background;
    background.load();

    auto player = new Player();
    GameObject* enemies[MAX_ENEMIES];
    Projectile* projectiles[MAX_PROJECTILES];
    PowerUp* powerUps[MAX_POWERUPS];
    int enemyCount = 0, projectileCount = 0, powerUpCount = 0;
    int score = 0;
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);

    Level level(1, WINDOW_WIDTH, 5, LevelType::FixedBoundary);
    Timer timer;
    float waveDelay = 5.0f, waveTimer = 0.0f, powerUpSpawnTimer = 0.0f;
    int enemiesDefeated = 0;
    int enemiesToDefeatToAdvance = 10;

    while (running) {
        canvas.checkInput();
        canvas.clear();

        if (canvas.keyPressed(VK_ESCAPE)) break;

        float deltaTime = timer.dt();
        waveTimer += deltaTime;
        powerUpSpawnTimer += deltaTime;

        // Calculate and display FPS
        int fps = static_cast<int>(1.0f / deltaTime);
        std::cout << "FPS: " << fps << " | Score: " << score << std::endl;

        // Spawn enemies at intervals defined by waveDelay
        if (waveTimer >= waveDelay) {
            waveTimer = 0.0f;
            level.spawnEnemies(enemies, enemyCount, player->getPosition());

            // Decrease waveDelay gradually, but not below a certain threshold
            if (waveDelay > 1.f) {
                waveDelay -= 0.1f;  // Reduce delay to make enemy spawning faster over time
            }
        }

        // Spawn PowerUps every 15 seconds
        if (powerUpSpawnTimer >= 15.0f) {
            powerUpSpawnTimer = 0.0f;
            if (powerUpCount < MAX_POWERUPS) {
                vec2 randomPos(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
                powerUps[powerUpCount++] = new PowerUp(randomPos);
            }
        }

        background.draw(canvas, camera);
        player->onUpdate(canvas, deltaTime, background, camera);

        if (player->getHealth() <= 0) {
            std::cout << "Game Over! Player has been destroyed." << std::endl;
            break;  // End the game if the player is dead
        }

        player->shootAtNearestEnemy(enemies, enemyCount, projectiles, projectileCount);

        if (canvas.keyPressed('Q')) {
            player->useAOEAttack(enemies, enemyCount);
        }

        if (canvas.keyPressed('L')) loadGame(player, enemies, enemyCount, score, "savegame.txt");
        if (canvas.keyPressed('K')) saveGame(player, enemies, enemyCount, score, "savegame.txt");

        camera.follow(player->getPosition());
        player->draw(canvas, camera.getPosition());

        for (int i = 0; i < enemyCount; ) {
            if (enemies[i]->getHealth() <= 0) {
                delete enemies[i];
                enemies[i] = enemies[--enemyCount];
                score += 10;  // Increment score when an enemy is defeated
            }
            else {
                enemies[i]->onUpdate(player->getPosition(), deltaTime);

                BomberEnemy* bomber = dynamic_cast<BomberEnemy*>(enemies[i]);
                DestroyerEnemy* destroyer = dynamic_cast<DestroyerEnemy*>(enemies[i]);
                SniperEnemy* sniper = dynamic_cast<SniperEnemy*>(enemies[i]);

                if (bomber) {
                    bomber->shootAtPlayer(player->getPosition(), projectiles, projectileCount);
                }

                if (destroyer) {
                    // Calculate the distance between the player and the destroyer
                    float distance = std::sqrt(
                        std::pow(player->getPosition().x - destroyer->getPosition().x, 2) +
                        std::pow(player->getPosition().y - destroyer->getPosition().y, 2)
                    );

                    if (distance <= destroyer->attackDistance) {
                        destroyer->explodeAndShoot(player->getPosition(), projectiles, projectileCount);
                        delete enemies[i];
                        enemies[i] = enemies[--enemyCount];  // Remove the destroyer after it shoots
                        continue;
                    }
                }

                if (sniper) {
                    sniper->shootAtPlayer(player->getPosition(), projectiles, projectileCount);
                }

                enemies[i]->draw(canvas, camera.getPosition());
                ++i;
            }
        }

        for (int i = 0; i < projectileCount; ++i) {
            projectiles[i]->onUpdate();
            projectiles[i]->draw(canvas, camera.getPosition());
        }

        for (int i = 0; i < powerUpCount; ++i) {
            powerUps[i]->draw(canvas, camera.getPosition());
        }

        CollisionManager::checkCollisions(player, enemies, enemyCount, projectiles, projectileCount, powerUps, powerUpCount, camera, enemiesDefeated);

        if (enemiesDefeated >= enemiesToDefeatToAdvance && level.getLevelType() == LevelType::FixedBoundary) {
            level.setLevelType(LevelType::InfiniteWorld);
            background.setInfiniteWorld(true);
            enemiesDefeated = 0;
            std::cout << "Level up! Switched to infinite world!" << std::endl;
        }

        canvas.present();
    }

    delete player;
    for (int i = 0; i < enemyCount; ++i) delete enemies[i];
    for (int i = 0; i < projectileCount; ++i) delete projectiles[i];
    for (int i = 0; i < powerUpCount; ++i) delete powerUps[i];

    return 0;
}
