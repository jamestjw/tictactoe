#include "board.h"
#include <algorithm>

Square::Square() {
    occupant = none;
} 

bool Square::empty() {
    return occupant == none;
}

void Square::occupy(Player p) {
    occupant = p;
}

Player Square::getPlayer() {
    return occupant;
}

void Square::draw() {
    switch (occupant) {
        case none:
            std::cout << " ";
            break;
        case player1:
            std::cout << "X";
            break;
        case player2:
            std::cout << "O";
            break;
    }
}

Board::Board() {
    gameOver = false;
    currentPlayer = player1;
    victor = none;
}  

std::string Board::currentPlayerName() {
    switch (currentPlayer) {
        case player1:
        case player2:
            return playerName(currentPlayer);
        default:
            std::cout << "Something went wrong!" << std::endl;
            exit(1);
    }
}


void Board::announcement() {
    if (!gameOver) {
        std::cout << "It is " << currentPlayerName() <<  "'s turn to play!" << std::endl;
        return;
    } else {
        switch (getVictor()) {
            case none:
                std::cout << "It was a a draw!" << std::endl;
                break;
            default:
                std::cout << playerName(victor) << " won!" << std::endl;
        }
    }
}

bool Board::squareIsEmpty(int i) {
    return squares[i].empty();
}

Player Board::getVictor() {
    return victor;
}

bool Board::isGameOver() {
    return gameOver;
}

void Board::draw() {
    for(int i = 0; i < 3 * BOARD_DIM + (BOARD_DIM - 1); i++) {
        for(int j = 0; j < 5 * BOARD_DIM + (BOARD_DIM - 1); j++) {
            // Draw borders
            if ((j + 1) % 6 == 0 || (i + 1) % 4 == 0) {
                    std::cout << "+";
            // Draw occupants of the squares
            } else if ((i - 1) % 4 == 0 && (j + 4) % 6 == 0) {
                // Work out index of square in the array of squares
                int index = BOARD_DIM * (i - 1) / 4 + (j - 2) / 6;

                // i 27 j 1
                squares[index].draw();
            } else {
                std::cout << " ";
            }

        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Board::evaluateWinConditions(std::vector<int> &indices, int *conditions, Player p) {
    bool row_failed = false;
    for (int j = 0; j < BOARD_DIM; j++)
    {
        if (!std::binary_search(indices.begin(), indices.end(), conditions[j])) {
            row_failed = true;
            break;
        }
    }

    if (!row_failed) {
        victor = p;
        gameOver = true;
        return true;
    }

    return false;
}

void Board::switchCurrentPlayer() {
    if (currentPlayer == player1) {
        currentPlayer = player2;
    } else {
        currentPlayer = player1;
    }
}

void Board::reevaluateGameState() {
    std::vector<int> player1Indices;
    std::vector<int> player2Indices;

    Player p;

    for (int i = 0; i < BOARD_DIM * BOARD_DIM; i++) {
        p = squares[i].getPlayer();
        if (p == player1) {
            player1Indices.push_back(i);
        } else if (p == player2) {
            player2Indices.push_back(i);
        }
    }

    bool skipPlayer1 = player1Indices.size() < BOARD_DIM;
    bool skipPlayer2 = player2Indices.size() < BOARD_DIM;

    if (!skipPlayer1 || !skipPlayer2) {
        // Winning configurations

        // Horizontal and vertical
        for (int i = 0; i < 3; i++) {
            int row_win_condition[BOARD_DIM];
            int col_win_condition[BOARD_DIM];
            for (int j = 0; j < BOARD_DIM; j++) {
                row_win_condition[j] = i * BOARD_DIM + j;
                col_win_condition[j] = j * BOARD_DIM + i;
            }
            

            if (!skipPlayer1) {
                if (evaluateWinConditions(player1Indices, row_win_condition, player1) || 
                    evaluateWinConditions(player1Indices, col_win_condition, player1)) {
                    return;
                }
            }
            
            if (!skipPlayer2) {
                if (evaluateWinConditions(player2Indices, row_win_condition, player2) ||
                    evaluateWinConditions(player2Indices, col_win_condition, player2)) {
                    return;
                }
            }
        }

        // Diagonal
        int diag_win_condition_1[BOARD_DIM] = {0, 4, 8};
        int diag_win_condition_2[BOARD_DIM] = {2, 4, 6};

        for (int k = 0; k < BOARD_DIM; k++) {
            diag_win_condition_1[k] = (BOARD_DIM + 1) * k;
            diag_win_condition_2[k] = (BOARD_DIM - 1) * (k + 1);
        }


        if (!skipPlayer1) {
            if (evaluateWinConditions(player1Indices, diag_win_condition_1, player1) || 
                    evaluateWinConditions(player1Indices, diag_win_condition_2, player1)) {
                return;
            }
        }
            
        if (!skipPlayer2) {
            if (evaluateWinConditions(player2Indices, diag_win_condition_1, player2) ||
                evaluateWinConditions(player2Indices, diag_win_condition_2, player2)) {
                return;
            }
        }
    }

    // Check if it was a draw
    if (player1Indices.size() + player2Indices.size() == BOARD_DIM * BOARD_DIM) {
        gameOver = true;
        return;
    }
}

void Board::occupySquare(int i) {
    squares[i].occupy(currentPlayer);
}

int obtainValidMove(Board *board)
{
    int playerInput;

    // Loops until the user gives us something that we can work with.
    while (true) 
    {
        std::cout << "Enter a number between 1 - " << BOARD_DIM*BOARD_DIM << " and hit enter: ";
        std::cin >> playerInput;
        
        if (std::cin.fail())
        {
            std::cout << "Invalid integer, please try again:";
        }
        
        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cin >> playerInput;
        }

        if (playerInput >= 1 && playerInput <= BOARD_DIM * BOARD_DIM) {
            if (board->squareIsEmpty(playerInput - 1)) {
                break;
            } else {
                std::cout << "That square is already occuped! Please try again. " << std::endl;
            }
        } else {
            std::cout << "That is an invalid number! Please try again. " << std::endl;
        }
    }

    return playerInput - 1;
}