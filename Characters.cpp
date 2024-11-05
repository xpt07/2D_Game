#include "Characters.h"

Characters::Characters(const std::string& sImage, vec2 startPos) : pos(startPos) {
    image.load(sImage);
}

void Characters::draw(Window& window, const vec2& position) {
    for (unsigned int i = 0; i < image.width; i++) {
        for (unsigned int j = 0; j < image.height; j++) {
            if (image.alphaAt(i, j) > 200) {
                window.draw(position.x + i, position.y + j, image.at(i, j));
            }
        }
    }
}
