#pragma once
#include <SFML/System/Vector2.hpp>

class Board {
public:
    Board(int width, int height);
    bool isInside(const sf::Vector2i& pos) const;

    int getWidth() const;
    int getHeight() const;

private:
    int width, height;
};