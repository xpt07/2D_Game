#pragma once
#include <iostream>
#include "GamesEngineeringBase.h"
#include "Camera.h"

const unsigned int MAX_TILES = 10;
const int MAX_SIZE = 1000;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

using namespace GamesEngineeringBase;

enum TileType {
	EMPTY_SPACE,
	STARFIELD,
	NEBULA,
	SMALL_ASTEROID,
	DENSE_ASTEROID,
	ASTEROID_CLUSTER
};

struct TileProperties {
	TileType type;
	bool passable;

	TileProperties(TileType type, bool passable)
		: type(type), passable(passable) {}
};

class tile {
public:
	tile(){}

	void load(string filename){
		if (!sprite.load(filename)) {
			std::cerr << "Error loading file: " << filename << std::endl;
		}
	}

	void draw(Window& canvas, int x, int y)
	{
		for (unsigned int i = 0; i < sprite.width; i++)
			if (y + i > 0 && (y + i) < (canvas.getWidth()))
				for (unsigned int n = 0; n < sprite.height; n++)
					if (y + n > 0 && (y + n) < canvas.getHeight())
						canvas.draw(n, y + i, sprite.atUnchecked(n, i));
	}

	bool isPassable() const { return passable; }
	void setPassable(bool passableState) { passable = passableState; }

private:
	Image sprite;
	bool passable = true;
};

class tileSet {
public:
	tileSet() { load(); }

	void load() {
		for (unsigned int i = 0; i < size; i++)
		{
			string filename;
			filename = "resources/background/bg" + to_string(i) + ".png";
			tiles[i].load(filename);
			tiles[i].setPassable(i < 3);
		}
	}

	tile& operator[](unsigned int index) { return tiles[index]; }

private:
	tile tiles[MAX_TILES];
	unsigned int size = MAX_TILES;
};

class Background
{
public:
	Background() {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		for (unsigned int i = 0; i < MAX_SIZE; i++) {
			a[i] = std::rand() % MAX_TILES;
		}
	}

	void draw(Window& canvas, const Camera& camera) {
		int camX = static_cast<int>(camera.getPosition().x);
		int camY = static_cast<int>(camera.getPosition().y);

		int tileX = camX / TILE_WIDTH;
		int tileY = camY / TILE_HEIGHT;
		int offsetX = camX % TILE_WIDTH;
		int offsetY = camY % TILE_HEIGHT;

		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				int drawX = (canvas.getWidth() / 2) - offsetX + (i * TILE_WIDTH);
				int drawY = (canvas.getHeight() / 2) - offsetY + (j * TILE_HEIGHT);

				int tileIndex = a[((tileY + j) * MAX_SIZE + (tileX + i)) % MAX_SIZE];
				tiles[tileIndex].draw(canvas, drawX, drawY);
			}
		}
	}

private:
	tileSet tiles;
	unsigned int a[MAX_SIZE];
};