#include "Characters.h"

Characters::Characters(string sImage, vec2 startPos):
	pos(startPos)
{
	image.load(sImage);
}

void Characters::draw(Window& w)
{

	window = w;

	for (unsigned int i = 0; i < image.width; i++)
	{
		for (unsigned int j = 0; j < image.height; j++)
		{
			if (image.alphaAt(i, j) > 200)
				w.draw(pos.x + i, pos.y + j, image.at(i, j));
		}
	}
}