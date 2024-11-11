#pragma once

#include "GamesEngineeringBase.h"
#include "vec2.h"
#include "Camera.h"
#include "Shape.h"
#include "circle.h"

/// @file core.h
/// @brief Defines core constants and includes necessary headers for the game engine.

/// @brief The width of the game window in pixels.
constexpr int WINDOW_WIDTH = 1024;

/// @brief The height of the game window in pixels.
constexpr int WINDOW_HEIGHT = 768;

/// @brief The speed at which the player moves.
constexpr float PLAYER_SPEED = 4.0f;

/// @brief The width of each tile in the game grid.
const int TILE_WIDTH = 32;

/// @brief The height of each tile in the game grid.
const int TILE_HEIGHT = 32;

/// @brief The number of tiles horizontally in the game grid.
const int GRID_WIDTH = 50;

/// @brief The number of tiles vertically in the game grid.
const int GRID_HEIGHT = 50;

/// @brief The maximum number of enemies that can be present in the game at one time.
const int MAX_ENEMIES = 100;

/// @brief The maximum number of projectiles that can be present in the game at one time.
const int MAX_PROJECTILES = 500;

/// @brief The maximum number of power-ups that can be present in the game at one time.
const int MAX_POWERUPS = 20;
