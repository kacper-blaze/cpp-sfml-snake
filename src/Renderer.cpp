#include "Renderer.hpp"

Renderer::Renderer(int tileSize)
    : tileSize(tileSize),
      tile(sf::Vector2f(tileSize, tileSize)) 
{
    tile.setOutlineThickness(1);
    tile.setOutlineColor(sf::Color::Black);
}

void Renderer::render(sf::RenderWindow& window,
                      const Snake& snake,
                      const Food& food) 
{
    tile.setFillColor(sf::Color::Green);

    for (const auto& segment : snake.getBody()) {
        tile.setPosition(segment.x * tileSize,
                         segment.y * tileSize);
        window.draw(tile);
    }

    tile.setFillColor(sf::Color::Red);
    sf::Vector2i pos = food.getPosition();
    tile.setPosition(pos.x * tileSize,
                     pos.y * tileSize);
    window.draw(tile);
}