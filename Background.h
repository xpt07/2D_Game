#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "core.h"

using namespace GamesEngineeringBase;

/// @file Background.h
/// @brief Defines classes for rendering a background with various tile types.

/// @enum TileType
/// @brief Enum for different types of background tiles.
enum TileType {
    MAIN_TILE,   ///< Represents a main, empty space tile.
    STARFIELD,   ///< Represents a tile with a starfield pattern.
    ASTEROID1,   ///< Represents a tile with the first type of asteroid.
    ASTEROID2    ///< Represents a tile with the second type of asteroid.
};

/// @class Tile
/// @brief Represents a single tile in the game's background.
class Tile {
public:
    /// @brief Default constructor for a Tile.
    Tile() = default;

    /**
     * @brief Loads an image file to use as the tile's texture.
     * @param filename The file path to the image.
     */
    void load(const std::string& filename) {
        if (!sprite.load(filename)) {
            std::cerr << "Error loading file: " << filename << std::endl;
        }
    }

    /**
     * @brief Draws the tile at a specified position on the canvas.
     * @param canvas The window canvas to draw on.
     * @param x The x-coordinate where the tile should be drawn.
     * @param y The y-coordinate where the tile should be drawn.
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
     * @brief Checks if a specific pixel in the tile is opaque.
     * @param x The x-coordinate of the pixel within the tile.
     * @param y The y-coordinate of the pixel within the tile.
     * @return True if the pixel is opaque, false otherwise.
     */
    bool isOpaque(int x, int y) {
        return sprite.alphaAt(x, y) > 200;  // 200 is used as an opacity threshold.
    }

private:
    Image sprite;  ///< The image used for the tile's appearance.
};

/// @class Background
/// @brief Manages the background tiles and supports infinite scrolling.
class Background {
public:
    /// @brief Constructs a Background with a default finite world setting.
    Background() : isInfiniteWorld(false) {}

    /**
     * @brief Loads tile images and initializes the tile grid with random tile types.
     */
    void load() {
        mainTile.load("resources/background/space_empty_tile.png");
        starfieldTile.load("resources/background/starfield_tile.png");
        asteroidTile.load("resources/background/asteroid_tile.png");
        asteroid2Tile.load("resources/background/asteroid2_tile.png");

        // Seed the random number generator for varied tile placement.
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Fill the tile grid with randomly selected tiles.
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                int randomValue = std::rand() % 100;  // Random value between 0 and 99.

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
     * @brief Draws the background tiles based on the camera's current position.
     * @param canvas The canvas to render the tiles on.
     * @param camera The camera used to determine the visible area.
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
                    // Wrap coordinates for seamless infinite scrolling.
                    gridX %= GRID_WIDTH;
                    gridY %= GRID_HEIGHT;
                    if (gridX < 0) gridX += GRID_WIDTH;
                    if (gridY < 0) gridY += GRID_HEIGHT;
                }
                else {
                    // Skip tiles outside the fixed world bounds.
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
     * @brief Sets whether the background should be infinite or fixed.
     * @param infinite True to enable infinite scrolling, false for a fixed world.
     */
    void setInfiniteWorld(bool infinite) { isInfiniteWorld = infinite; }

    /**
     * @brief Checks if the world is infinite or not.
     * @return True if the world is infinite, false otherwise.
     */
    bool IsInfiniteWorld() const { return isInfiniteWorld; }

    /**
     * @brief Determines if a given position is blocked by an obstacle tile.
     * @param position The position to check.
     * @param camera The camera used for view adjustments.
     * @return True if the position is blocked, false otherwise.
     */
    bool isPositionBlocked(const vec2& position, Camera& camera) const {
        int playerWidth = 32;  // Assumed width of the player.
        int playerHeight = 32; // Assumed height of the player.

        float halfWidth = playerWidth / 2.0f;
        float halfHeight = playerHeight / 2.0f;

        // Array of corners to check for collisions.
        vec2 corners[4] = {
            {position.x - halfWidth, position.y - halfHeight},  // Top-left corner
            {position.x + halfWidth, position.y - halfHeight},  // Top-right corner
            {position.x - halfWidth, position.y + halfHeight},  // Bottom-left corner
            {position.x + halfWidth, position.y + halfHeight}   // Bottom-right corner
        };

        for (int i = 0; i < 4; ++i) {
            vec2 corner = corners[i];
            int gridX = (static_cast<int>(corner.x) / TILE_WIDTH) % GRID_WIDTH;
            int gridY = (static_cast<int>(corner.y) / TILE_HEIGHT) % GRID_HEIGHT;

            if (gridX < 0) gridX += GRID_WIDTH;
            if (gridY < 0) gridY += GRID_HEIGHT;

            TileType tileType = tileGrid[gridY][gridX];
            if (tileType == ASTEROID1 || tileType == ASTEROID2) {
                return true;  // The position is blocked.
            }
        }
        return false;  // No obstacles found.
    }

private:
    Tile mainTile; ///< The main background tile.
    Tile starfieldTile; ///< The starfield tile.
    Tile asteroidTile; ///< The first type of asteroid tile.
    Tile asteroid2Tile; ///< The second type of asteroid tile.

    TileType tileGrid[GRID_HEIGHT][GRID_WIDTH]; ///< Grid layout of tiles.
    bool isInfiniteWorld; ///< Indicates if the background is infinite.
};
