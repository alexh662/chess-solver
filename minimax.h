#ifndef MINIMAX_H
#define MINIMAX_H

#include "board.h"
#include "evaluate.h"
#include <vector>

void generatePawnMoves(Board& board, int i, int j, std::vector<Move>& moves);
void generateBishopMoves(Board& board, int i, int j, std::vector<Move>& moves);
void generateKnightMoves(Board& board, int i, int j, std::vector<Move>& moves);
void generateRookMoves(Board& board, int i, int j, std::vector<Move>& moves);
void generateQueenMoves(Board& board, int i, int j, std::vector<Move>& moves);
void generateKingMoves(Board& board, int i, int j, std::vector<Move>& moves);

std::vector<Move> generateMoves(Board& board, bool whiteToMove);

Move bestMove(Board& board, int depth, bool whiteToMove);

int minimax(Board& board, int depth, bool whiteToMove, bool maximizingPlayer);

#endif