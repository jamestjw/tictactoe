#ifndef BOARD_H
#define BOARD_H

#include "iostream"
#include <vector>
#include "player.h"

const int BOARD_DIM = 3;

class Square { 
    private:   
        Player occupant;
    
    public:
        Square();

        // Returns true if the square is empty.
        bool empty();

        // Occupy the square with a player's piece
        void occupy(Player p);

        // Returns the player that is occupying this square
        Player getPlayer();

        // Draw this square.
        void draw();
};

// Represents an n-by-n board.
class Board {
    private:
        Square squares[BOARD_DIM * BOARD_DIM];
        bool gameOver;
        Player victor;
        Player currentPlayer;

    public:
        Board();

        std::string currentPlayerName();
        // Announcement to be showed at the top of the game,
        // this usually changes after each turn.
        void announcement();

        // When the board dimension is 3,
        // we visualise each individual square on the board as a 3x5 grid.
        // Taking into account the borders, we require a 11x17 grid for the
        // entire board.
        void draw();
        
        // Occupy square i with current player.
        void occupySquare(int i);
        
        bool isGameOver();

        Player getVictor();

        // Check if a particular square is empty.
        bool squareIsEmpty(int i);

        // Check if any player has won or if the game has been drawn
        // and update the board state accordingly.
        void reevaluateGameState();

        // Switch the current player to the other player.
        void switchCurrentPlayer();

        // Given a vector of indices where a player has placed
        // his pieces, and another int array of a win condition,
        // evaluate whether a particular player has won the game.
        // Returns true when someone wins the game
        bool evaluateWinConditions(std::vector<int> &indices, int *conditions, Player p);
};

// Returns a number between 0 and BOARD_DIM^2 - 1 corresponding to the squares
// on the tic-tac-toe board based on user input.
int obtainValidMove(Board *board);

#endif