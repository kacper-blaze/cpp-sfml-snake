# Snake Game with AI Spectate Mode

A classic Snake game implemented in C++ using SFML (Simple and Fast Multimedia Library)
featuring both manual gameplay and an intelligent AI spectate mode where you can watch the computer play using advanced pathfinding.

## Features

- 🐍 **Classic Snake Gameplay**: Control a snake that grows when eating food
- 🎮 **Smooth Controls**: Use arrow keys to control the snake's direction
- 🍎 **Food System**: Food spawns randomly on free tiles
- 💥 **Collision Detection**: Game ends when snake hits walls or itself
- 🎯 **Game States**: Start menu, gameplay, and game over screen
- 🔄 **Restart Functionality**: Press SPACE to restart after game over
- 🎨 **Clean Visuals**: Green snake, red food on a black background
- 🤖 **AI Spectate Mode**: Watch an intelligent AI play the game automatically!

## How to play

- Use arrow keys to control the snake's direction
- Press SPACE to start the game
- Press S to spectate AI gameplay
- Press SPACE to restart after game over
- Press S to spectate AI after game over

## Game rules

- The snake starts with one segment
- Each food eaten makes the snake grow by one segment
- The snake moves continuously in the current direction
- Game ends if the snake hits the boundary or itself
- The snake cannot reverse direction directly (e.g., can't go from Left to Right)

### AI Behavior
The AI uses intelligent decision-making:
- **Food Seeking**: Uses Manhattan distance to prioritize movement toward food
- **Collision Avoidance**: Checks all directions for safe moves before deciding
- **Self-Preservation**: Avoids reversing direction into its own body
- **Fallback Strategy**: When direct food paths are blocked, chooses safest available direction

### AI Algorithm
The AI uses a custom pathfinding approach:
1. Calculates Manhattan distance to food: `|x1-x2| + |y1-y2|`
2. Prioritizes directions based on shortest distance to food
3. Validates each direction for collisions (walls and snake body)
4. Falls back to survival mode when food-seeking moves are unsafe

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
