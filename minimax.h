#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"
#include "evaluate.h"
#include "generateMoves.h"
#include <vector>

Move bestMove(Board& board, int depth, bool whiteToMove);

int minimax(Board& board, int depth, bool whiteToMove, bool maximizingPlayer);

#endif