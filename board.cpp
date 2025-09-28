#include <iostream>
#include <vector>
#include "board.h"

using namespace std;

Board::Board() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j].type = EMPTY;
      board[i][j].colour = NONE;
    }
  }

  board[0][0] = Piece(ROOK, BLACK);
  board[0][1] = Piece(KNIGHT, BLACK);
  board[0][2] = Piece(BISHOP, BLACK);
  board[0][3] = Piece(QUEEN, BLACK);
  board[0][4] = Piece(KING, BLACK);
  board[0][5] = Piece(BISHOP, BLACK);
  board[0][6] = Piece(KNIGHT, BLACK);
  board[0][7] = Piece(ROOK, BLACK);
  for(int i = 0; i < 8; i++) board[1][i] = Piece(PAWN, BLACK);

  board[7][0] = Piece(ROOK, WHITE);
  board[7][1] = Piece(KNIGHT, WHITE);
  board[7][2] = Piece(BISHOP, WHITE);
  board[7][3] = Piece(QUEEN, WHITE);
  board[7][4] = Piece(KING, WHITE);
  board[7][5] = Piece(BISHOP, WHITE);
  board[7][6] = Piece(KNIGHT, WHITE);
  board[7][7] = Piece(ROOK, WHITE);
  for(int i = 0; i < 8; i++) board[6][i] = Piece(PAWN, WHITE);
}

Move Board::stringToMove(string s) {
  int fCol = s[0] - 'a';
  int fRow = 8 - (s[1] - '0');
  int tCol = s[2] - 'a';
  int tRow = 8 - (s[3] - '0');
  
  Piece promo;

  if (s.length() > 4) {
    char c = toupper(s[4]);
    PieceType pt;

    switch (c) {
        case 'Q': pt = QUEEN; break;
        case 'R': pt = ROOK; break;
        case 'B': pt = BISHOP; break;
        case 'N': pt = KNIGHT; break;
        default: pt = EMPTY; break;
    }

    promo = Piece(pt, board[fRow][fCol].colour);
  }

  Move m = Move(fRow, fCol, tRow, tCol, board[fRow][fCol], board[tRow][tCol], promo);
  return m;
}

void Board::makeMove(Move& move) {
  Piece piece = board[move.fRow][move.fCol];
  board[move.fRow][move.fCol] = Piece();

  if (move.promotion.type == EMPTY) {
    board[move.tRow][move.tCol] = piece;
  } else {
    board[move.tRow][move.tCol] = Piece(move.promotion.type, piece.colour);
  }

  move.prevEnPassantCords = enPassantCords;
  move.prevEnPassant = enPassant;

  // check if first pawn move for en passant
  if (piece.type == PAWN && ((move.fRow == 6 && move.tRow == 4) || (move.fRow == 1 && move.tRow == 3))) {
    enPassantCords = {move.tRow, move.tCol};
    enPassant = true;
  } else enPassant = false;

  // en passant
  move.enPassantCapture = false;
  if (piece.type == PAWN && move.tCol != move.fCol && move.capturedPiece.type == PAWN && board[move.tRow][move.tCol].type == EMPTY) {
    board[move.fRow][move.tCol] = Piece();
    move.enPassantCapture = true;
  }

  if (move.movedPiece.type == KING) {
    if (move.movedPiece.colour == WHITE) whiteKingCords = {move.tRow, move.tCol};
    else if (move.movedPiece.colour == BLACK) blackKingCords = {move.tRow, move.tCol};
  }
}

void Board::undoMove(Move& move) {
  board[move.fRow][move.fCol] = move.movedPiece;

  if (move.enPassantCapture) {
    int captureRow = move.movedPiece.colour == WHITE ? move.tRow + 1 : move.tRow - 1;
    board[captureRow][move.tCol] = move.capturedPiece;
    board[move.tRow][move.tCol] = Piece();
  } else {
    board[move.tRow][move.tCol] = move.capturedPiece;
  }

  enPassantCords = move.prevEnPassantCords;
  enPassant = move.prevEnPassant;

  if (move.movedPiece.type == KING) {
    if (move.movedPiece.colour == WHITE) whiteKingCords = {move.fRow, move.fCol};
    else if (move.movedPiece.colour == BLACK) blackKingCords = {move.fRow, move.fCol};
  }
}

Piece Board::getPiece(int row, int col) {
  return board[row][col];
}

void Board::printBoard() {
  for (int i = 0; i < 8; i++) {
    cout << "\033[35m" << 8 - i << " " << "\033[0m";
    for (int j = 0; j < 8; j++) {
      Piece piece = board[i][j];
      string output;

      if (piece.type == PAWN) output = "p ";
      else if (piece.type == BISHOP) output = "b ";
      else if (piece.type == KNIGHT) output = "n ";
      else if (piece.type == ROOK) output = "r ";
      else if (piece.type == QUEEN) output = "q ";
      else if (piece.type == KING) output = "k ";
      else output = ". ";

      if (piece.colour == WHITE) {
        for (char& c : output) {
          c = toupper(c);
        }
      }

      cout << output;
    }
    cout << endl;
  }
  cout << "  ";
  for (char c = 'a'; c <= 'h'; c++) cout << "\033[36m" << c << " ";
  cout << "\033[0m" << endl << endl;
}