#include "AI.h"
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

Direction PathFinder::getNextDirection(const sf::Vector2i& snakeHead, 
                                     const std::vector<sf::Vector2i>& snakeBody,
                                     const sf::Vector2i& food,
                                     int boardWidth, int boardHeight,
                                     Direction currentDirection) {

    sf::Vector2i toFood = food - snakeHead;

    std::vector<std::pair<sf::Vector2i, Direction>> directions;

    if (abs(toFood.x) > abs(toFood.y)) {
        if (toFood.x > 0) directions.push_back({{1, 0}, Direction::Right});
        if (toFood.x < 0) directions.push_back({{-1, 0}, Direction::Left});
        if (toFood.y > 0) directions.push_back({{0, 1}, Direction::Down});
        if (toFood.y < 0) directions.push_back({{0, -1}, Direction::Up});
    } else {
        if (toFood.y > 0) directions.push_back({{0, 1}, Direction::Down});
        if (toFood.y < 0) directions.push_back({{0, -1}, Direction::Up});
        if (toFood.x > 0) directions.push_back({{1, 0}, Direction::Right});
        if (toFood.x < 0) directions.push_back({{-1, 0}, Direction::Left});
    }

    std::vector<std::pair<sf::Vector2i, Direction>> allDirections = {
        {{1, 0}, Direction::Right},
        {{0, 1}, Direction::Down},
        {{-1, 0}, Direction::Left},
        {{0, -1}, Direction::Up}
    };

    for (auto& dir : allDirections) {
        bool alreadyAdded = false;
        for (auto& added : directions) {
            if (added.second == dir.second) {
                alreadyAdded = true;
                break;
            }
        }
        if (!alreadyAdded) {
            directions.push_back(dir);
        }
    }

    for (auto& [delta, dir] : directions) {
        sf::Vector2i nextPos = snakeHead + delta;

        if (dir == opposite(currentDirection)) {
            continue;
        }

        if (nextPos.x >= 0 && nextPos.x < boardWidth &&
            nextPos.y >= 0 && nextPos.y < boardHeight) {

            bool isOccupied = false;
            for (const auto& segment : snakeBody) {
                if (nextPos == segment) {
                    isOccupied = true;
                    break;
                }
            }

            if (!isOccupied) {
                return dir;
            }
        }
    }

    return getSurvivalDirection(snakeHead, snakeBody, boardWidth, boardHeight, currentDirection);
}

Direction PathFinder::getSurvivalDirection(const sf::Vector2i& snakeHead,
                                          const std::vector<sf::Vector2i>& snakeBody,
                                          int boardWidth, int boardHeight,
                                          Direction currentDirection) {

    std::vector<std::pair<sf::Vector2i, Direction>> directions = {
        {{1, 0}, Direction::Right},
        {{0, 1}, Direction::Down},
        {{-1, 0}, Direction::Left},
        {{0, -1}, Direction::Up}
    };

    for (auto& [delta, dir] : directions) {
        sf::Vector2i nextPos = snakeHead + delta;

        if (dir == opposite(currentDirection)) {
            continue;
        }

        if (nextPos.x < 0 || nextPos.x >= boardWidth ||
            nextPos.y < 0 || nextPos.y >= boardHeight) {
            continue; // Out of bounds
            }

        bool isOccupied = false;
        for (const auto& segment : snakeBody) {
            if (nextPos == segment) {
                isOccupied = true;
                break;
            }
        }

        if (!isOccupied) {
            return dir;
        }
    }

    return Direction::Right;
}

int PathFinder::calculateAccessibleArea(const sf::Vector2i& start,
                                      const std::vector<sf::Vector2i>& obstacles,
                                      int boardWidth, int boardHeight) {

    struct Vector2iHash {
        std::size_t operator()(const sf::Vector2i& v) const {
            return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
        }
    };

    std::unordered_set<sf::Vector2i, Vector2iHash> visited;
    std::queue<sf::Vector2i> toVisit;

    toVisit.push(start);
    visited.insert(start);

    int count = 0;

    while (!toVisit.empty() && count < 50) {
        sf::Vector2i current = toVisit.front();
        toVisit.pop();
        count++;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                if (abs(dx) + abs(dy) != 1) continue;

                sf::Vector2i neighbor = current + sf::Vector2i(dx, dy);

                if (isValid(neighbor, boardWidth, boardHeight) &&
                    !isObstacle(neighbor, obstacles) &&
                    !visited.count(neighbor)) {

                    visited.insert(neighbor);
                    toVisit.push(neighbor);
                }
            }
        }
    }

    return count;
}

std::vector<sf::Vector2i> PathFinder::findPath(const sf::Vector2i& start,
                                              const sf::Vector2i& goal,
                                              const std::vector<sf::Vector2i>& obstacles,
                                              int boardWidth, int boardHeight) {

    struct Vector2iHash {
        std::size_t operator()(const sf::Vector2i& v) const {
            return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
        }
    };

    std::unordered_set<sf::Vector2i, Vector2iHash> closedSet;
    std::unordered_map<sf::Vector2i, Node*, Vector2iHash> openSetMap;
    std::priority_queue<Node> openSet;
    std::vector<Node*> allNodes;

    Node* startNode = new Node{start, 0, 0, heuristic(start, goal), nullptr};
    allNodes.push_back(startNode);
    openSet.push(*startNode);
    openSetMap[start] = startNode;

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.pos == goal) {
            std::vector<sf::Vector2i> path;
            Node* node = openSetMap[current.pos];
            while (node) {
                path.push_back(node->pos);
                node = node->parent;
            }
            std::reverse(path.begin(), path.end());

            for (auto* node : allNodes) delete node;
            return path;
        }

        closedSet.insert(current.pos);

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                if (abs(dx) + abs(dy) != 1) continue;

                sf::Vector2i neighborPos = current.pos + sf::Vector2i(dx, dy);

                if (!isValid(neighborPos, boardWidth, boardHeight) ||
                    isObstacle(neighborPos, obstacles) ||
                    closedSet.count(neighborPos) ||
                    openSetMap.count(neighborPos)) {
                    continue;
                }

                int g = current.g + 1;
                int h = heuristic(neighborPos, goal);
                int f = g + h;

                Node* neighbor = new Node{neighborPos, f, g, h, openSetMap[current.pos]};
                allNodes.push_back(neighbor);
                openSet.push(*neighbor);
                openSetMap[neighborPos] = neighbor;
            }
        }
    }

    for (auto* node : allNodes) delete node;
    return {};
}

int PathFinder::heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
    return abs(a.x - b.x) + abs(a.y - b.y); // Manhattan distance
}

bool PathFinder::isValid(const sf::Vector2i& pos, int boardWidth, int boardHeight) {
    return pos.x >= 0 && pos.x < boardWidth && pos.y >= 0 && pos.y < boardHeight;
}

bool PathFinder::isObstacle(const sf::Vector2i& pos, const std::vector<sf::Vector2i>& obstacles) {
    for (const auto& obstacle : obstacles) {
        if (pos == obstacle) return true;
    }
    return false;
}