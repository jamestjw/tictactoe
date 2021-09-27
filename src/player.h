#ifndef PLAYER_H
#define PLAYER_H

#include <string>

enum Player {
    none, 
    player1, 
    player2 
};

std::string playerName(Player p);

#endif