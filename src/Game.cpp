#include "Game.hpp"
#include "Board.hpp"
#include "Snake.hpp"
#include "Food.hpp"

Game::Game()
    : window(sf::VideoMode(600, 600), "Snake"),
      board(20, 20),
      renderer(30)
{
    food.respawn(getFreeTiles());

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        throw std::runtime_error("Failed to load DejaVuSans font");
    }

    titleText.setFont(font);
    titleText.setString("SNAKE GAME");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    centerText(titleText, 150);

    startText.setFont(font);
    startText.setString("Press SPACE to Start");
    startText.setCharacterSize(24);
    startText.setFillColor(sf::Color::White);
    centerText(startText, 250);

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    centerText(gameOverText, 150);

    restartText.setFont(font);
    restartText.setString("Press SPACE to Restart");
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::White);
    centerText(restartText, 250);
}

void Game::centerText(sf::Text& text, float yPosition) {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition((600 - textBounds.width) / 2, yPosition);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();

        if (currentState == GameState::Playing) {
            update();
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                if (currentState == GameState::Menu) {
                    startGame();
                } else if (currentState == GameState::GameOver) {
                    restartGame();
                }
            }

            if (currentState == GameState::Playing) {
                if (event.key.code == sf::Keyboard::Up)
                    snake.setDirection(Direction::Up);
                else if (event.key.code == sf::Keyboard::Down)
                    snake.setDirection(Direction::Down);
                else if (event.key.code == sf::Keyboard::Left)
                    snake.setDirection(Direction::Left);
                else if (event.key.code == sf::Keyboard::Right)
                    snake.setDirection(Direction::Right);
            }
        }
    }
}

std::vector<sf::Vector2i> Game::getFreeTiles() const {
    std::vector<sf::Vector2i> freeTiles;

    for (int x = 0; x < board.getWidth(); ++x) {
        for (int y = 0; y < board.getHeight(); ++y) {
            sf::Vector2i pos(x, y);

            if (snake.occupies(pos)) continue;

            if (pos == food.getPosition()) continue;

            freeTiles.push_back(pos);
        }
    }

    return freeTiles;
}

void Game::update() {
    if (isGameOver) return;

    if (clock.getElapsedTime().asSeconds() >= moveDelay) {

        snake.move();
        clock.restart();

        if (!board.isInside(snake.getHead())) {
            gameOver();
            return;
        }

        if (snake.checkSelfCollision()) {
            gameOver();
            return;
        }

        if (snake.getHead() == food.getPosition()) {
            snake.grow();

            auto freeTiles = getFreeTiles();
            if (freeTiles.empty()) {
                hasWon = true;
                gameOver();
                return;
            }

            food.respawn(freeTiles);
        }
    }
}

void Game::render() {
    window.clear();

    if (currentState == GameState::Menu) {
        renderMenu();
    } else if (currentState == GameState::Playing) {
        renderer.render(window, snake, food);
    } else if (currentState == GameState::GameOver) {
        renderer.render(window, snake, food);
        renderGameOver();
    }

    window.display();
}
void Game::gameOver() {
    isGameOver = true;
    currentState = GameState::GameOver;
}

void Game::startGame() {
    currentState = GameState::Playing;
    isGameOver = false;
    clock.restart();
}

void Game::restartGame() {
    snake = Snake();
    food.respawn(getFreeTiles());
    isGameOver = false;
    hasWon = false;
    currentState = GameState::Playing;
    clock.restart();
}

void Game::renderMenu() {
    window.draw(titleText);
    window.draw(startText);
}

void Game::renderGameOver() {
    if (hasWon) {
        gameOverText.setString("YOU WIN!");
        gameOverText.setFillColor(sf::Color::Green);
    } else {
        gameOverText.setString("GAME OVER");
        gameOverText.setFillColor(sf::Color::Red);
    }
    window.draw(gameOverText);
    window.draw(restartText);
}
