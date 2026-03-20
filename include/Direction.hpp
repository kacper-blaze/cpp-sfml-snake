#pragma once
#include <cstdint>

enum class Direction : std::uint8_t {
    Up,
    Down,
    Left,
    Right
};

inline Direction opposite(Direction dir) {
    switch (dir) {
        case Direction::Up: return Direction::Down;
        case Direction::Down: return Direction::Up;
        case Direction::Left: return Direction::Right;
        case Direction::Right: return Direction::Left;
    }
    return dir;
}