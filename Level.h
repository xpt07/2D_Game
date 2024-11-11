#pragma once

#include "Player.h"
#include "Enemy.h"

/// @file Level.h
/// @brief Defines the Level class, responsible for managing enemy spawning and level properties.

/// @brief Enum representing the type of the level.
enum class LevelType {
    FixedBoundary,  ///< The level has fixed boundaries.
    InfiniteWorld   ///< The level has infinite scrolling behavior.
};

/// @class Level
/// @brief Manages the spawning of enemies and the type of level.
class Level {
public:
    /// @brief Constructs a Level object with specified parameters.
    /// @param _waveNumber The number of the current wave.
    /// @param _waveRadius The radius within which enemies can spawn around the player.
    /// @param _enemiesPerWave The number of enemies to spawn per wave.
    /// @param type The type of the level (e.g., FixedBoundary or InfiniteWorld).
    Level(int _waveNumber, float _waveRadius, int _enemiesPerWave, LevelType type);

    /// @brief Spawns enemies in the game world based on the player's position.
    /// @param enemies The array of enemies to be populated.
    /// @param enemyCount The current count of enemies.
    /// @param playerPos The position of the player, used to determine enemy spawn locations.
    void spawnEnemies(GameObject* enemies[], int& enemyCount, vec2 playerPos);

    /// @brief Gets the current level type.
    /// @return The type of the level (FixedBoundary or InfiniteWorld).
    LevelType getLevelType() const { return currentLevelType; }

    /// @brief Sets the current level type.
    /// @param type The new type of the level.
    void setLevelType(LevelType type) { currentLevelType = type; }

private:
    int waveNumber;           ///< The current wave number.
    float waveRadius;         ///< The radius around the player within which enemies spawn.
    int enemiesPerWave;       ///< The number of enemies to spawn per wave.
    LevelType currentLevelType; ///< The type of the level (e.g., FixedBoundary or InfiniteWorld).
};
