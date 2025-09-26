#include <iostream>
#include "evaluate.h"
#include <vector>

int evaluateBoard(Board& board) {
  double pieceValues[7] = {0, 1, 3.2, 3.33, 5.1, 9.5, 1000};
  double val = 0;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Piece piece = board.getPiece(i, j);

      if (piece.colour == WHITE) val += pieceValues[piece.type];
      else if (piece.colour == BLACK) val -= pieceValues[piece.type];
    }
  }

  return val;
}