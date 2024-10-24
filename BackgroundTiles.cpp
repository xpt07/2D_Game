#include "BackgroundTiles.h"

BackgroundTiles::BackgroundTiles()
{
	for (int i = 0; i < 6; i++)
	{
		tiles[i].load("resources/background/Space_Background" + std::to_string(i) + ".png");
	}
}

void BackgroundTiles::draw(Window& canvas)
{
	//for (unsigned int i = 0; i < canvas.getWidth(); i++)
	//	for (unsigned int j = 0; j < canvas.getHeight(); j++)
	//		for (int x = 0; x < 6; i++)
	//			/*if (tiles[x].alphaAt(i, j) > 0)*/
	//			canvas.draw(i, j, tiles[x].atUnchecked(i, j));
}
