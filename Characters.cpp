#include "Characters.h"

Characters::Characters(string sImage)
{
	image.load(sImage);
}

void Characters::draw(Window& w)
{
	window = w;
	unsigned int planeX = w.getWidth() / 2 - (image.width / 2);
	unsigned int planeY = w.getHeight() / 2 - (image.height / 2);

	for (unsigned int i = 0; i < image.width; i++)
	{
		for (unsigned int j = 0; j < image.height; j++)
		{
			if (image.alphaAt(i, j) > 200)
				w.draw(planeX + i, planeY + j, image.at(i, j));
		}
	}
}