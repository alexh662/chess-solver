#include <iostream>
#include <vector>
#include "board.h"
#include "evaluate.h"
#include "generateMoves.h"
#include "minimax.h"
#include "threadPool.h"

using namespace std;

int main() {
  int depth = 6;
  Threadpool threadPool(std::thread::hardware_concurrency());

  Board board = Board();
  board.printBoard();

  while (isGameOver(board, false) == ONGOING && isGameOver(board, true) == ONGOING) {
    string s;
    cout << "enter move: ";
    cin >> s;
    Move m = board.stringToMove(s);
    board.makeMove(m);
    board.printBoard();

    pair<Move, double> best = bestMove(board, depth, false, threadPool);
    board.makeMove(best.first);
    board.printBoard();
  }

  return -1;
}