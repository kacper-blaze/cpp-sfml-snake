#pragma once

#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "Food.hpp"

class Renderer {
public:
    Renderer(int tileSize);

    void render(sf::RenderWindow& window,
                const Snake& snake,
                const Food& food);

private:
    int tileSize;
    sf::RectangleShape tile;
};