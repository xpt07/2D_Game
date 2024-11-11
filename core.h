#pragma once

#include "GamesEngineeringBase.h"
#include "vec2.h"
#include "Camera.h"

#include "Shape.h"
#include "circle.h"

constexpr int WINDOW_WIDTH = 1024;
constexpr int WINDOW_HEIGHT = 768;
constexpr float PLAYER_SPEED = 4.0f;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int GRID_WIDTH = 50; 
const int GRID_HEIGHT = 50;

const int MAX_ENEMIES = 100;
const int MAX_PROJECTILES = 500;
const int MAX_POWERUPS = 20;