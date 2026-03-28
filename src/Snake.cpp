#include "Snake.hpp"

Snake::Snake() {
    body.push_back(sf::Vector2i(10, 10));
    direction = Direction::Right;
}

Direction Snake::getDirection() const {
    return direction;
}

void Snake::move() {
    sf::Vector2i head = body.front();

    switch (direction) {
        case Direction::Up:    head.y -= 1; break;
        case Direction::Down:  head.y += 1; break;
        case Direction::Left:  head.x -= 1; break;
        case Direction::Right: head.x += 1; break;
    }

    body.insert(body.begin(), head);
    if (!shouldGrow) {
        body.pop_back();
    } else {
        shouldGrow = false;
    }
}
void Snake::grow() {
    shouldGrow = true;
}
void Snake::setDirection(Direction dir) {
    if (dir != opposite(direction)) {
        direction = dir;
    }
}
bool Snake::checkSelfCollision() const {
    for (auto it = body.begin() + 1; it != body.end(); ++it) {
        if (*it == body.front()) {
            return true;
        }
    }
    return false;
}

bool Snake::occupies(const sf::Vector2i& pos) const {
    for (const auto& segment : body) {
        if (segment == pos) {
            return true;
        }
    }
    return false;
}

std::vector<sf::Vector2i> Snake::getBody() const {
    return body;
}
sf::Vector2i Snake::getHead() const {
    return body.front();
}