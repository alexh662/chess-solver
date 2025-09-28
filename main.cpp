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
  Move m = Move(6, 3, 4, 3, board.getPiece(6, 3));
  board.makeMove(m);
  m = Move(1, 2, 2, 2, board.getPiece(1, 2));
  board.makeMove(m);
  m = Move(0, 3, 3, 0, board.getPiece(0, 3));
  board.makeMove(m);
  m = Move(3, 0, 3, 3, board.getPiece(0, 3));
  board.makeMove(m);
  m = Move(3, 3, 4, 3, board.getPiece(3, 3));
  board.makeMove(m);
  board.printBoard();
  vector<Move> moves = generateMoves(board, true);
  printMoves(moves);

  pair<Move, double> best = bestMove(board, 4, true);
  printMove(best.first);
  cout << ", " << best.second << endl;

  return -1;
}