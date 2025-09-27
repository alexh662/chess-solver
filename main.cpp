#include <iostream>
#include <vector>
#include "board.h"
#include "evaluate.h"
#include "generateMoves.h"
#include "minimax.h"

using namespace std;

int main() {
  Board board = Board();
  board.printBoard();
  cout << evaluateBoard(board) << endl;
  board.makeMove(Move(6, 3, 4, 3, Piece()));
  board.makeMove(Move(6, 5, 4, 5, Piece()));
  board.printBoard();
  vector<Move> moves = generateMoves(board, true);
  printMoves(moves);

  return -1;
}