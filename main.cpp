#include <iostream>
#include "board.h"
#include "evaluate.h"

using namespace std;

int main() {
  Board board = Board();
  board.printBoard();
  Move move = Move(6, 4, 4, 4);
  board.makeMove(move);
  board.printBoard();
  cout << evaluateBoard(board) << endl;

  return -1;
}