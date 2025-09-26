#ifndef BOARD_H
#define BOARD_H

#include <utility>
#include <vector>

enum PieceType { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
enum Colour { WHITE, BLACK, NONE };

struct Piece {
  PieceType type;
  Colour colour;

  Piece(PieceType t = EMPTY, Colour c = NONE) : type(t), colour(c) {}
};

struct Move {
  int fRow, fCol;
  int tRow, tCol;
  Piece movedPiece;
  Piece capturedPiece;
  Piece promotion;

  Move(int fRow_, int fCol_, int tRow_, int tCol_, Piece movedPiece_, Piece capturedPiece_ = Piece(), Piece promotion_ = Piece()) : fRow(fRow_), fCol(fCol_), tRow(tRow_), tCol(tCol_), movedPiece(movedPiece_), capturedPiece(capturedPiece_), promotion(promotion_) {}
};

class Board {
public:
  Piece board[8][8];
  std::pair<int, int> enPassantCords;
  bool enPassant = false;

  Board();

  void makeMove(const Move& move);

  void undoMove(const Move& move);

  Piece getPiece(int row, int col);

  void printBoard();
};

#endif