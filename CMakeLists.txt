cmake_minimum_required(VERSION 4.1)
project(snakeGame)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(snakeGame
        src/main.cpp
        src/main.cpp
        src/Game.cpp
        src/Snake.cpp
        src/Food.cpp
        src/Board.cpp
        src/Renderer.cpp
)
        find_package(SFML 2.5 COMPONENTS graphics network audio system REQUIRED)
        target_link_libraries(snakeGame sfml-graphics sfml-network sfml-audio sfml-system)
