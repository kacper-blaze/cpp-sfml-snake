#pragma once

#include "Direction.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>

class Snake {
public:
    Snake();
    ~Snake() = default;

    void move();
    void grow();
    void setDirection(Direction dir);
    bool checkSelfCollision() const;
    Direction getDirection() const;

    bool occupies(const sf::Vector2i& pos) const;

    sf::Vector2i getHead() const;
    std::vector<sf::Vector2i> getBody() const;

private:
    std::vector<sf::Vector2i> body;
    Direction direction;
    bool shouldGrow = false;
};