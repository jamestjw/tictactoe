# tictactoe

A simple tictactoe game. To change the dimension of the tictactoe board, change the `BOARD_DIM`constant in the `board.h` file.


## Execution

Build the game using `cmake`.

```bash
mkdir build
cd build
cmake ..
cmake --build .
./tictactoe
```

Build using `g++`.

```bash
g++ src/*.cpp -o tictactoe
./tictactoe
```
