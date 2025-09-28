#include <iostream>
#include "minimax.h"
#include <vector>
#include <algorithm>

using namespace std;

State isGameOver(Board& board, bool whiteToMove) {
  vector<Move> moves = generateMoves(board, whiteToMove);

  if (moves.empty()) {
    if (whiteToMove && inCheck(board, board.whiteKingCords.first, board.whiteKingCords.second)) return WHITEWINS;
    else if (!whiteToMove && inCheck(board, board.blackKingCords.first, board.blackKingCords.second)) return BLACKWINS;
    else return STALEMATE;
  }

  return ONGOING;
}

pair<Move, double> bestMove(Board& board, int depth, bool whiteToMove) {
  vector<Move> moves = generateMoves(board, whiteToMove);
  Move best = moves[0];
  double bestEval = whiteToMove ? -100000 : 100000;

  for (Move m : moves) {
    board.makeMove(m);
    double eval = minimax(board, depth - 1, !whiteToMove);
    board.undoMove(m);

    if (whiteToMove && eval > bestEval) {
      best = m;
      bestEval = eval;
    } else if (!whiteToMove && eval < bestEval) {
      best = m;
      bestEval = eval;
    }
  }

  return {best, bestEval};
}

double minimax(Board& board, int depth, bool whiteToMove) {
  if (depth == 0 || isGameOver(board, whiteToMove)) return evaluateBoard(board);

  if (whiteToMove) {
    double maxEval = -100000;
    for (Move m : generateMoves(board, whiteToMove)) {
      board.makeMove(m);
      maxEval = max(maxEval, minimax(board, depth - 1, false));
      board.undoMove(m);
    }
    return maxEval;
  } else {
    double minEval = 100000;
    for (Move m : generateMoves(board, whiteToMove)) {
      board.makeMove(m);
      minEval = min(minEval, minimax(board, depth - 1, true));
      board.undoMove(m);
    }
    return minEval;
  }
}
