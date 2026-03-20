# Snake Game

A classic Snake game implemented in C++ using SFML (Simple and Fast Multimedia Library).

## Features

- 🐍 **Classic Snake Gameplay**: Control a snake that grows when eating food
- 🎮 **Smooth Controls**: Use arrow keys to control the snake's direction
- 🍎 **Food System**: Food spawns randomly on free tiles
- 💥 **Collision Detection**: Game ends when snake hits walls or itself
- 🎯 **Game States**: Start menu, gameplay, and game over screen
- 🔄 **Restart Functionality**: Press SPACE to restart after game over
- 🎨 **Clean Visuals**: Green snake, red food on a black background

## How to play

- Use arrow keys to control the snake's direction
- Press SPACE to start the game
- Press SPACE to restart after game over

## Game rules

- The snake starts with one segment
- Each food eaten makes the snake grow by one segment
- The snake moves continuously in the current direction
- Game ends if the snake hits the boundary or itself
- The snake cannot reverse direction directly (e.g., can't go from Left to Right)

## Requirements

- **C++17** or higher
- **SFML 2.5** or higher
- **CMake** 3.10 or higher
- **Linux** (tested on Ubuntu/Debian with DejaVu Sans font)

## Installation

### Prerequisites

Install SFML development libraries:

```bash
# Ubuntu/Debian
sudo apt-get install libsfml-dev

# Fedora
sudo dnf install SFML-devel

# Arch Linux
sudo pacman -S sfml
```
```dockerignore
snakeGame/
├── include/           # Header files
│   ├── Game.hpp
│   ├── Snake.hpp
│   ├── Food.hpp
│   ├── Board.hpp
│   ├── Renderer.hpp
│   ├── Direction.hpp
│   └── GameState.hpp
├── src/               # Source files
│   ├── main.cpp
│   ├── Game.cpp
│   ├── Snake.cpp
│   ├── Food.cpp
│   ├── Board.cpp
│   └── Renderer.cpp
├── CMakeLists.txt     # Build configuration
└── README.md          # This file
```
