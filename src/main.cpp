#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <assert.h>
#include "board.h"
#include "player.h"

using namespace std;

void clearScreen()
{
    // Clear screen by printing new lines
    cout << string(100, '\n');
}


int main() 
{
    // BOARD_DIM must be an odd number greater or equal to 3.
    assert ((BOARD_DIM + 1) % 2 == 0 && BOARD_DIM >= 3);

    Board board;
    int playerInput;


    cout << "Welcome to TicTacToe!" << endl;
    cout << "Press ENTER to start the game." << endl;
    getchar();    

    while (true) {
        clearScreen();

        board.announcement();

        board.draw();

        if (board.isGameOver()) {
            cout << "Press ENTER to start a new game." << endl;
            getchar();
            getchar(); // Not sure why 2 getchars are needed to make this work
            board = Board();
            continue;
        }

        playerInput = obtainValidMove(&board);

        board.occupySquare(playerInput);   
        board.reevaluateGameState();
        board.switchCurrentPlayer();    
    }
}