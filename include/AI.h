#pragma once
#include "Direction.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <set>

class PathFinder {
public:
    static Direction getNextDirection(const sf::Vector2i& snakeHead,
                               const std::vector<sf::Vector2i>& snakeBody,
                               const sf::Vector2i& food,
                               int boardWidth, int boardHeight,
                               Direction currentDirection);

    static Direction getSurvivalDirection(const sf::Vector2i &snakeHead, const std::vector<sf::Vector2i> &snakeBody,
                                       int boardWidth, int boardHeight, Direction currentDirection);

private:
    struct Node {
        sf::Vector2i pos;
        int f, g, h;
        Node* parent;

        bool operator<(const Node& other) const {
            return f > other.f;
        }
    };

    static Direction getSurvivalDirection(const sf::Vector2i& snakeHead,
                                     const std::vector<sf::Vector2i>& snakeBody,
                                     int boardWidth, int boardHeight);

    static int calculateAccessibleArea(const sf::Vector2i& start,
                                      const std::vector<sf::Vector2i>& obstacles,
                                      int boardWidth, int boardHeight);

    static std::vector<sf::Vector2i> findPath(const sf::Vector2i& start,
                                              const sf::Vector2i& goal,
                                              const std::vector<sf::Vector2i>& obstacles,
                                              int boardWidth, int boardHeight);

    static int heuristic(const sf::Vector2i& a, const sf::Vector2i& b);
    static bool isValid(const sf::Vector2i& pos, int boardWidth, int boardHeight);
    static bool isObstacle(const sf::Vector2i& pos, const std::vector<sf::Vector2i>& obstacles);
};