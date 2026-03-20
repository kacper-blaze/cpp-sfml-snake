#include "Board.hpp"

Board::Board(int width, int height)
    : width(width), height(height) {}

int Board::getWidth() const {
    return width;
}
int Board::getHeight() const {
    return height;
}

bool Board::isInside(const sf::Vector2i& pos) const {
    return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
}


