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

void Board::makeMove(const Move& move) {
  Piece piece = board[move.fRow][move.fCol];
  board[move.fRow][move.fCol] = Piece(EMPTY, NONE);

  if (move.promotion.type == EMPTY) {
    board[move.tRow][move.tCol] = piece;
  } else {
    board[move.tRow][move.tCol] = Piece(move.promotion.type, piece.colour);
  }
}

Piece Board::getPiece(int row, int col) {
  return board[row][col];
}

void Board::printBoard() {
  for (int i = 0; i < 8; i++) {
    cout << "\033[35m" << i + 1 << " " << "\033[0m";
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