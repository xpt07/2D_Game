#pragma once
#include <iostream>
#include "GamesEngineeringBase.h"
#include "Camera.h"

const unsigned int MAX_TILES = 10;
const int MAX_SIZE = 1000;

using namespace GamesEngineeringBase;
class tile {
public:
	tile(){}

	void load(string filename){
		sprite.load(filename);
	}

	void draw(Window& canvas, int y)
	{
		for (unsigned int i = 0; i < sprite.height; i++)
			if (y + i > 0 && (y + i) < (canvas.getHeight()))
				for (unsigned int n = 0; n < sprite.width; n++)
					canvas.draw(n, y + i, sprite.atUnchecked(n, i));
	}

private:
	Image sprite;
};

class tileSet {
public:
	tileSet(){}

	void load() {
		for (unsigned int i = 0; i < size; i++)
		{
			string filename;
			filename = "resources/background/bg" + to_string(i) + ".png";
			tiles[i].load(filename);
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
		tiles.load();

		for (unsigned int i = 0; i < MAX_SIZE; i++)
			a[i] = rand() % MAX_TILES;
	}

	void draw(Window& canvas, int wy) {
		int height = 768;
		int Y = wy / height;
		int r = wy % height;
		tiles[a[Y % MAX_SIZE]].draw(canvas, (canvas.getHeight() / 2) + r);
		tiles[a[(Y + 1) % MAX_SIZE]].draw(canvas, r);
		tiles[a[(Y + 2) % MAX_SIZE]].draw(canvas, -height + r);
	}

private:
	tileSet tiles;
	unsigned int a[MAX_SIZE];
};