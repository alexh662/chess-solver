#ifndef BOARD_H
#define BOARD_H

#include <utility>
#include <vector>
#include <string>

enum PieceType { EMPTY, PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING};
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
  bool enPassantCapture;
  std::pair<int, int> prevEnPassantCords;
  bool prevEnPassant;

  Move(int fRow_, int fCol_, int tRow_, int tCol_, Piece movedPiece_, Piece capturedPiece_ = Piece(), Piece promotion_ = Piece(), bool enPassantCapture_ = false)
  : fRow(fRow_), fCol(fCol_), tRow(tRow_), tCol(tCol_), movedPiece(movedPiece_), capturedPiece(capturedPiece_), promotion(promotion_), enPassantCapture(enPassantCapture_), prevEnPassantCords({-1, -1}), prevEnPassant(false) {}
};

class Board {
public:
  Piece board[8][8];
  std::pair<int, int> enPassantCords;
  bool enPassant = false;
  std::pair<int, int> whiteKingCords = {7, 4};
  std::pair<int, int> blackKingCords = {0, 4};

  Board();

  Move stringToMove(std::string s);

  void makeMove(Move& move);

  void undoMove(Move& move);

  Piece getPiece(int row, int col);

  void printBoard();
};

#endif