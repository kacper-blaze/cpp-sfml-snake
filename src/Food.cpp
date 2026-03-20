#include "Food.hpp"
#include <cstdlib>
#include <SFML/System/Vector2.hpp>
#include "Board.hpp"
#include "Snake.hpp"

void Food::respawn(const std::vector<sf::Vector2i>& freeTiles) {
    if (freeTiles.empty()) return;

    int index = std::rand() % freeTiles.size();
    position = freeTiles[index];
}

sf::Vector2i Food::getPosition() const { return position; }