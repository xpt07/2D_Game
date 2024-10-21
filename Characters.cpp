#include "Characters.h"

Characters::Characters(string sImage, unsigned int startX, unsigned int startY):
	x(startX), y(startY)
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
				w.draw(x + i, y + j, image.at(i, j));
		}
	}
}