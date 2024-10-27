#include "Background.h"

Background::Background()
{
    for (int i = 0; i < MAX_TILES; ++i) {

        tiles[i].load("resources/background/Space_Background" + std::to_string(i) + ".png");

        if (!tiles[i].load("resources/background/Space_Background" + std::to_string(i) + ".png"))
            std::cerr << "Failed to load tile: " << i << std::endl;
    }
    if (MAX_TILES > 0) {
        tileWidth = tiles[0].width;
        tileHeight = tiles[0].height;
    }
}

void Background::draw(Window& canvas, const Camera& camera)
{
    int screenWidth = canvas.getWidth();
    int screenHeight = canvas.getHeight();

    // Calculate starting tile indices based on the camera's position
    int startTileX = (camera.offsetX() / tileWidth) % MAX_TILES;
    int startTileY = (camera.offsetY() / tileHeight) % MAX_TILES;

    // Offset within the tile for smooth scrolling
    int offsetX = camera.offsetX() % tileWidth;
    int offsetY = camera.offsetY() % tileHeight;

    // Draw tiles across the canvas, covering the entire screen area
    for (int y = -1; y <= screenHeight / tileHeight; ++y) {
        for (int x = -1; x <= screenWidth / tileWidth; ++x) {
            // Calculate the current tile's index in the array, wrapping around as needed
            int tileIndexX = (startTileX + x + MAX_TILES) % MAX_TILES;
            int tileIndexY = (startTileY + y + MAX_TILES) % MAX_TILES;
            GamesEngineeringBase::Image& tile = tiles[(tileIndexY * MAX_TILES + tileIndexX) % MAX_TILES];

            // Calculate where to draw this tile on the canvas
            int drawX = x * tileWidth - offsetX;
            int drawY = y * tileHeight - offsetY;

            // Ensure we are drawing within the canvas bounds
            for (int ty = 0; ty < tile.height; ++ty) {
                for (int tx = 0; tx < tile.width; ++tx) {
                    // Calculate canvas coordinates for the pixel
                    int canvasX = drawX + tx;
                    int canvasY = drawY + ty;

                    // Only draw if the pixel is within the canvas bounds
                    if (canvasX >= 0 && canvasX < screenWidth && canvasY >= 0 && canvasY < screenHeight) {
                        unsigned char* pixel = tile.at(tx, ty);
                        canvas.draw(canvasX, canvasY, pixel[0], pixel[1], pixel[2]);
                    }
                }
            }
        }
    }
}
