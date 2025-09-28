#ifndef GENERATEMOVES_H
#define GENERATEMOVES_H

#include "board.h"
#include "evaluate.h"
#include <vector>

void addMove(Board& board, std::vector<Move>& moves, Move move);

bool inCheck(Board& board, int i, int j);

void generatePawnMoves(Board& board, int i, int j, std::vector<Move>& moves);
void generateBishopMoves(Board& board, int i, int j, std::vector<Move>& moves);
void generateKnightMoves(Board& board, int i, int j, std::vector<Move>& moves);
void generateRookMoves(Board& board, int i, int j, std::vector<Move>& moves);
void generateQueenMoves(Board& board, int i, int j, std::vector<Move>& moves);
void generateKingMoves(Board& board, int i, int j, std::vector<Move>& moves);

std::vector<Move> generateMoves(Board& board, bool whiteToMove);

void printMove(Move& move);

void printMoves(std::vector<Move>& moves);

#endif