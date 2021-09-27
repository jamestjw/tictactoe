cmake_minimum_required( VERSION 3.0 )

project( tictactoe )

include_directories( ./include ./src )

add_executable( tictactoe ./src/main.cpp ./src/player.cpp ./src/board.cpp)

