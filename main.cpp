#include <iostream>
#include "board.h"
#include "evaluate.h"

using namespace std;

int main() {
  Board board = Board();
  board.makeMove(Move(6, 4, 4, 4, board.getPiece(6, 4)));
  board.makeMove(Move(4, 4, 2, 4, board.getPiece(6, 4)));
  board.makeMove(Move(2, 4, 1, 3, board.getPiece(2, 4), board.getPiece(1, 3)));
  Move move = Move(1, 3, 0, 2, board.getPiece(1, 3), board.getPiece(0, 2));
  board.makeMove(move);
  board.printBoard();
  board.undoMove(move);
  board.printBoard();
  cout << evaluateBoard(board) << endl;

  return -1;
}