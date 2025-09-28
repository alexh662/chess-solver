#include <iostream>
#include "minimax.h"
#include <vector>
#include <algorithm>

using namespace std;

State isGameOver(Board& board, bool whiteToMove) {
  vector<Move> moves = generateMoves(board, whiteToMove);

  if (moves.empty()) {
    if (whiteToMove && inCheck(board, board.whiteKingCords.first, board.whiteKingCords.second)) return BLACKWINS;
    else if (!whiteToMove && inCheck(board, board.blackKingCords.first, board.blackKingCords.second)) return WHITEWINS;
    else return STALEMATE;
  }

  return ONGOING;
}

pair<Move, double> bestMove(Board& board, int depth, bool whiteToMove) {
  vector<Move> moves = generateMoves(board, whiteToMove);
  if (moves.empty()) return {Move(0, 0, 0, 0, board.getPiece(0, 0)), whiteToMove ? -100000 : 100000};
  Move best = moves[0];
  double bestEval = whiteToMove ? -100000 : 100000;

  for (Move m : moves) {
    board.makeMove(m);
    double eval = minimax(board, depth - 1, -100000, 100000, !whiteToMove);
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

double minimax(Board& board, int depth, double alpha, double beta, bool whiteToMove) {
  if (depth == 0 || isGameOver(board, whiteToMove) != ONGOING) return evaluateBoard(board);

  if (whiteToMove) {
    double maxEval = -100000;
    for (Move m : generateMoves(board, whiteToMove)) {
      board.makeMove(m);
      double eval = minimax(board, depth - 1, alpha, beta, false);
      board.undoMove(m);
      maxEval = max(maxEval, eval);
      alpha = max(alpha, eval);
      if (beta <= alpha) break;
    }
    return maxEval;
  } else {
    double minEval = 100000;
    for (Move m : generateMoves(board, whiteToMove)) {
      board.makeMove(m);
      double eval = minimax(board, depth - 1, alpha, beta, true);
      board.undoMove(m);
      minEval = min(minEval, eval);
      beta = min(beta, eval);
      if (beta <= alpha) break;
    }
    return minEval;
  }
}
