#include "player.h"

std::string playerName(Player p) {   
    switch (p) {
        case player1:
            return "Player 1";
        case player2:
            return "Player 2";
        default:
            return "";
    }
}