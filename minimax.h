#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"
#include "evaluate.h"
#include "generateMoves.h"
#include <vector>
#include <string>
#include <utility>

class Threadpool;

enum State { ONGOING, STALEMATE, WHITEWINS, BLACKWINS };

State isGameOver(Board& board, bool whiteToMove);

std::pair<Move, double> bestMove(Board& board, int depth, bool whiteToMove, Threadpool& threadPool);

double minimax(Board& board, int depth, double alpha, double beta, bool whiteToMove);

#endif