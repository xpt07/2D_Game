#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "core.h"

using namespace GamesEngineeringBase;

// Define tile types with an enum for easy reference
enum TileType {
    MAIN_TILE,
    STARFIELD,
    ASTEROID1,
    ASTEROID2
};

class Tile {
public:
    Tile() = default;

    // Load the tile image from a file
    void load(const std::string& filename) {
        if (!sprite.load(filename)) {
            std::cerr << "Error loading file: " << filename << std::endl;
        }
    }

    // Draw the tile at the given position on the canvas
    void draw(Window& canvas, int x, int y) {
        for (unsigned int i = 0; i < sprite.width; i++) {
            if (x + i >= 0 && (x + i) < canvas.getWidth()) {
                for (unsigned int j = 0; j < sprite.height; j++) {
                    if (y + j >= 0 && (y + j) < canvas.getHeight()) {
                        canvas.draw(x + i, y + j, sprite.atUnchecked(i, j));
                    }
                }
            }
        }
    }

    bool isOpaque(int x, int y) {
        return sprite.alphaAt(x, y) > 200;  // Assuming 200 as the threshold for opacity
    }

private:
    Image sprite;
};

class Background {
public:
    Background() : isInfiniteWorld(false) {}

    // Load all tile images and initialize the random grid
    void load() {
        mainTile.load("resources/background/space_empty_tile.png");
        starfieldTile.load("resources/background/starfield_tile.png");
        asteroidTile.load("resources/background/asteroid_tile.png");
        asteroid2Tile.load("resources/background/asteroid2_tile.png");

        // Seed random number generator for variety in the tile grid
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Fill the tile grid with random tiles
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                int randomValue = std::rand() % 100;  // Generate a number from 0 to 99

                if (randomValue < 1) {
                    tileGrid[y][x] = ASTEROID1;
                }
                else if (randomValue < 1.5) {
                    tileGrid[y][x] = ASTEROID2;
                }
                else if (randomValue < 49) {
                    tileGrid[y][x] = MAIN_TILE;
                }
                else {
                    tileGrid[y][x] = STARFIELD;
                }
            }
        }
    }

    // Draw the background based on the camera position, creating an infinite scrolling effect
    void draw(Window& canvas, const Camera& camera) {
        int camX = static_cast<int>(camera.getPosition().x);
        int camY = static_cast<int>(camera.getPosition().y);

        int offsetX = camX % TILE_WIDTH;
        int offsetY = camY % TILE_HEIGHT;

        int tilesX = (canvas.getWidth() / TILE_WIDTH) + 2;
        int tilesY = (canvas.getHeight() / TILE_HEIGHT) + 2;

        for (int i = -1; i < tilesX - 1; i++) {
            for (int j = -1; j < tilesY - 1; j++) {
                int gridX = (camX / TILE_WIDTH + i);
                int gridY = (camY / TILE_HEIGHT + j);

                if (isInfiniteWorld) {
                    // Wrap coordinates for infinite scrolling
                    gridX %= GRID_WIDTH;
                    gridY %= GRID_HEIGHT;
                    if (gridX < 0) gridX += GRID_WIDTH;
                    if (gridY < 0) gridY += GRID_HEIGHT;
                }
                else {
                    // Check boundaries for fixed world
                    if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) continue;
                }

                TileType tileType = tileGrid[gridY][gridX];
                int drawX = (i * TILE_WIDTH) - offsetX;
                int drawY = (j * TILE_HEIGHT) - offsetY;

                switch (tileType) {
                case MAIN_TILE: mainTile.draw(canvas, drawX, drawY); break;
                case STARFIELD: starfieldTile.draw(canvas, drawX, drawY); break;
                case ASTEROID1: asteroidTile.draw(canvas, drawX, drawY); break;
                case ASTEROID2: asteroid2Tile.draw(canvas, drawX, drawY); break;
                default: break;
                }
            }
        }
    }

    void setInfiniteWorld(bool infinite) { isInfiniteWorld = infinite; }
    bool IsInfiniteWorld() const { return isInfiniteWorld; }

    bool isPositionBlocked(const vec2& position, Camera& camera) const {

        // Player's bounding box dimensions
        int playerWidth = 48;  // Adjust based on your player's actual width
        int playerHeight = 48; // Adjust based on your player's actual height

        // Calculate the offset to center the bounding box around the player's position
        float halfWidth = playerWidth / 2.0f;
        float halfHeight = playerHeight / 2.0f;

        // Check all four corners of the player's bounding box
        std::vector<vec2> corners = {
            {position.x - halfWidth, position.y - halfHeight},             // Top-left corner
            {position.x + halfWidth, position.y - halfHeight},             // Top-right corner
            {position.x - halfWidth, position.y + halfHeight},             // Bottom-left corner
            {position.x + halfWidth, position.y + halfHeight}              // Bottom-right corner
        };

        for (const vec2& corner : corners) {
            // Convert the corner's world coordinates to grid coordinates
            int gridX = (static_cast<int>(corner.x) / TILE_WIDTH) % GRID_WIDTH;
            int gridY = (static_cast<int>(corner.y) / TILE_HEIGHT) % GRID_HEIGHT;

            // Ensure grid coordinates are non-negative (handle negative positions)
            if (gridX < 0) gridX += GRID_WIDTH;
            if (gridY < 0) gridY += GRID_HEIGHT;

            // Check if the tile at the grid coordinates is an asteroid
            TileType tileType = tileGrid[gridY][gridX];
            if (tileType == ASTEROID1 || tileType == ASTEROID2) {
                return true;  // Collision detected with an impassable tile
            }
        }

        return false;  // No collision detected
    }

private:
    Tile mainTile, starfieldTile, asteroidTile, asteroid2Tile;

    // 2D array to hold the layout of tiles for infinite scrolling
    TileType tileGrid[GRID_HEIGHT][GRID_WIDTH];

    bool isInfiniteWorld;
};
