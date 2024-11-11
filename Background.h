#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "core.h"

using namespace GamesEngineeringBase;

/// Enumeration for different tile types used in the background
enum TileType {
    MAIN_TILE,   ///< Main tile with no special properties
    STARFIELD,   ///< Tile representing a starfield
    ASTEROID1,   ///< Tile representing the first type of asteroid
    ASTEROID2    ///< Tile representing the second type of asteroid
};

/// Class representing a single tile in the background
class Tile {
public:
    /// Default constructor for the Tile class
    Tile() = default;

    /**
     * @brief Loads the tile image from a specified file
     *
     * @param filename The path to the image file
     */
    void load(const std::string& filename) {
        if (!sprite.load(filename)) {
            std::cerr << "Error loading file: " << filename << std::endl;
        }
    }

    /**
     * @brief Draws the tile at a specified position on the canvas
     *
     * @param canvas The canvas on which to draw the tile
     * @param x The x-coordinate of the top-left corner
     * @param y The y-coordinate of the top-left corner
     */
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

    /**
     * @brief Checks if a given pixel position in the tile is opaque
     *
     * @param x The x-coordinate within the tile
     * @param y The y-coordinate within the tile
     * @return True if the pixel is opaque, otherwise false
     */
    bool isOpaque(int x, int y) {
        return sprite.alphaAt(x, y) > 200;  // Assuming 200 as the threshold for opacity
    }

private:
    Image sprite;  ///< The image representing the tile
};

/// Class representing the background of the game, supporting infinite scrolling and tile-based rendering
class Background {
public:
    /// Constructor for the Background class, initializes the world to be finite
    Background() : isInfiniteWorld(false) {}

    /**
     * @brief Loads all tile images and initializes the tile grid with random tiles
     */
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

    /**
     * @brief Draws the background based on the camera position, creating an infinite scrolling effect
     *
     * @param canvas The canvas to draw on
     * @param camera The camera providing the current view position
     */
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

    /**
     * @brief Sets whether the world is infinite or fixed
     *
     * @param infinite True for infinite scrolling, false for a fixed world
     */
    void setInfiniteWorld(bool infinite) { isInfiniteWorld = infinite; }

    /**
     * @brief Checks if the world is infinite
     *
     * @return True if the world is infinite, otherwise false
     */
    bool IsInfiniteWorld() const { return isInfiniteWorld; }

    /**
     * @brief Checks if a given position is blocked by an impassable tile
     *
     * @param position The position to check
     * @param camera The camera used to adjust for the current view
     * @return True if the position is blocked, otherwise false
     */
    bool isPositionBlocked(const vec2& position, Camera& camera) const {
        // Player's bounding box dimensions
        int playerWidth = 48;  // Adjust based on your player's actual width
        int playerHeight = 48; // Adjust based on your player's actual height

        // Calculate the offset to center the bounding box around the player's position
        float halfWidth = playerWidth / 2.0f;
        float halfHeight = playerHeight / 2.0f;

        // Check all four corners of the player's bounding box
        vec2 corners[4] = {
            {position.x - halfWidth, position.y - halfHeight},  // Top-left corner
            {position.x + halfWidth, position.y - halfHeight},  // Top-right corner
            {position.x - halfWidth, position.y + halfHeight},  // Bottom-left corner
            {position.x + halfWidth, position.y + halfHeight}   // Bottom-right corner
        };

        for (int i = 0; i < 4; ++i) {
            vec2 corner = corners[i];
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
    Tile mainTile;           ///< Tile representing the main background
    Tile starfieldTile;      ///< Tile representing the starfield
    Tile asteroidTile;       ///< Tile representing the first type of asteroid
    Tile asteroid2Tile;      ///< Tile representing the second type of asteroid

    TileType tileGrid[GRID_HEIGHT][GRID_WIDTH];  ///< 2D array for the tile grid layout
    bool isInfiniteWorld;    ///< Flag indicating if the world is infinite
};
