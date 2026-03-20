#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Board.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Renderer.hpp"
#include "Direction.hpp"
#include "GameState.hpp"

class Game {
public:
    Game();
    void run();

    std::vector<sf::Vector2i> getFreeTiles() const;

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    Board board;
    Snake snake;
    Food food;
    Renderer renderer;

    sf::Clock clock;
    float moveDelay = 0.15f;

    bool isGameOver = false;
    bool hasWon = false;

    void gameOver();

    GameState currentState = GameState::Menu;
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;
    sf::Text gameOverText;
    sf::Text restartText;

    void startGame();
    void restartGame();
    void renderMenu();
    void renderGameOver();

    void centerText(sf::Text& text, float yPosition);
};
