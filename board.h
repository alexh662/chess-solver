#ifndef BOARD_H
#define BOARD_H

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
  Piece promotion;

  Move(int fRow_, int fCol_, int tRow_, int tCol_, Piece promotion_ = Piece()) : fRow(fRow_), fCol(fCol_), tRow(tRow_), tCol(tCol_) {}
};

class Board {
public:
  Piece board[8][8];

  Board();

  void makeMove(const Move& move);

  Piece getPiece(int row, int col);

  void printBoard();
};

#endif