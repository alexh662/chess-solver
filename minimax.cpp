#include <iostream>
#include "minimax.h"
#include <vector>

using namespace std;

Move bestMove(Board& board, int depth, bool whiteToMove);

int minimax(Board& board, int depth, bool whiteToMove, bool maximizingPlayer) {
  if (depth == 0) return evaluateBoard(board);
}
