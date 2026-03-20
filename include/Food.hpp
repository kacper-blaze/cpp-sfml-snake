#pragma once
#include <SFML/System/Vector2.hpp>

#include "Board.hpp"
#include "Snake.hpp"

class Food {
public:
    void respawn(const std::vector<sf::Vector2i>& freeTiles);
    sf::Vector2i getPosition() const;

private:
    sf::Vector2i position;
};
