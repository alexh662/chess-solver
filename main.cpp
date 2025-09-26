#include <iostream>
#include "board.h"

using namespace std;

int main() {
  Board board = Board();
  board.printBoard();
  Move move = Move(6, 4, 4, 4);
  board.makeMove(move);
  board.printBoard();

  return -1;
}