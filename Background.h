#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "GamesEngineeringBase.h"
#include "Camera.h"

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int GRID_WIDTH = 50;  // Dimensions for the random tile grid
const int GRID_HEIGHT = 50;

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

private:
    Image sprite;
};

class Background {
public:
    Background() = default;

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

        // Calculate the number of tiles to cover the screen
        int tilesX = (canvas.getWidth() / TILE_WIDTH) + 2;
        int tilesY = (canvas.getHeight() / TILE_HEIGHT) + 2;

        // Loop over a grid to draw tiles in a 3x3 pattern around the camera
        for (int i = -1; i < tilesX - 1; i++) {
            for (int j = -1; j < tilesY - 1; j++) {
                // Wrap the tile grid around to create an infinite effect
                int gridX = (camX / TILE_WIDTH + i) % GRID_WIDTH;
                int gridY = (camY / TILE_HEIGHT + j) % GRID_HEIGHT;

                // Ensure we wrap correctly for negative positions
                if (gridX < 0) gridX += GRID_WIDTH;
                if (gridY < 0) gridY += GRID_HEIGHT;

                // Select the tile type from the grid
                TileType tileType = tileGrid[gridY][gridX];

                // Calculate where to draw this tile on the screen
                int drawX = (i * TILE_WIDTH) - offsetX;
                int drawY = (j * TILE_HEIGHT) - offsetY;

                switch (tileType)
                {
                case MAIN_TILE:
                    mainTile.draw(canvas, drawX, drawY);
                    break;
                case STARFIELD:
                    starfieldTile.draw(canvas, drawX, drawY);
                    break;
                case ASTEROID1:
                    asteroidTile.draw(canvas, drawX, drawY);
                    break;
                case ASTEROID2:
                    asteroid2Tile.draw(canvas, drawX, drawY);
                    break;
                default:
                    break;
                }
            }
        }
    }

private:
    Tile mainTile;
    Tile starfieldTile;
    Tile asteroidTile;
    Tile asteroid2Tile;

    // 2D array to hold the layout of tiles for infinite scrolling
    TileType tileGrid[GRID_HEIGHT][GRID_WIDTH];
};
