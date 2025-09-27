#include <iostream>
#include <vector>
#include <utility>
#include "generateMoves.h"

using namespace std;

void generatePawnMoves(Board& board, int i, int j, vector<Move>& moves) {
  Piece piece = board.getPiece(i, j);
  int direction = 1;
  if (piece.colour == WHITE) direction = -1;

  if ((direction == 1 && i + direction < 8) || (direction == -1 && i + direction >= 0)) {
    for (int k = -1; k <= 1; k++) {
      if (j + k >= 0 && j + k < 8) {
        if (k != 0) {
          if ((board.getPiece(i + direction, j + k).colour == WHITE && piece.colour == BLACK) || (board.getPiece(i + direction, j + k).colour == BLACK && piece.colour == WHITE)) {
            if ((direction == 1 && i + direction == 7) || (direction == -1 && i + direction == 0)) for (int p = 2; p <= 5; p++) {
              Piece promo = Piece(static_cast<PieceType>(p), piece.colour);
              moves.push_back(Move(i, j, i + direction, j + k, piece, board.getPiece(i + direction, j + k), promo));
            }
            moves.push_back(Move(i, j, i + direction, j + k, piece, board.getPiece(i + direction, j + k)));
          } else if (board.enPassant && board.enPassantCords.first == i + direction && board.enPassantCords.second == j + k) moves.push_back(Move(i, j, i + direction, j + k, piece, board.getPiece(i, j + k)));
        } else if (board.getPiece(i + direction, j).type == EMPTY) {
          if ((direction == 1 && i + direction == 7) || (direction == -1 && i + direction == 0)) for (int p = 2; p <= 5; p++) {
            Piece promo = Piece(static_cast<PieceType>(p), piece.colour);
            moves.push_back(Move(i, j, i + direction, j, piece, Piece(), promo));
          }
          moves.push_back(Move(i, j, i + direction, j, piece));

          if (piece.colour == WHITE && i == 6 && board.getPiece(i - 2, j).type == EMPTY) moves.push_back(Move(i, j, i - 2, j, piece));
          else if (piece.colour == BLACK && i == 1 && board.getPiece(i + 2, j).type == EMPTY) moves.push_back(Move(i, j, i + 2, j, piece));
        }
      }
    }
  }
}

void generateBishopMoves(Board& board, int i, int j, vector<Move>& moves) {
  Piece piece = board.getPiece(i, j);

  for (int k = -1; k <= 1; k += 2) {
    for (int l = -1; l <= 1; l += 2) {
      int m = 1;
      bool end = false;
      while (i + k*m >= 0 && i + k*m < 8 && j + l*m >= 0 && j + l*m < 8 && !end) {
        if (board.getPiece(i + k*m, j + l*m).type != EMPTY) {
          end = true;
          if (board.getPiece(i + k*m, j + l*m).colour != piece.colour) moves.push_back(Move(i, j, i + k*m, j + l*m, piece, board.getPiece(i + k*m, j + l*m)));
        } else moves.push_back(Move(i, j, i + k*m, j + l*m, piece));
        m++;
      }
    }
  }
}

void generateKnightMoves(Board& board, int i, int j, vector<Move>& moves) {
  Piece piece = board.getPiece(i, j);
  vector<pair<int, int>> knightMoves = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

  for (int k = 0; k < 8; k++) {
    if (i + knightMoves[k].first >= 0 && i + knightMoves[k].first < 8 && j + knightMoves[k].second >= 0 && j + knightMoves[k].second < 8) {
      if (board.getPiece(i + knightMoves[k].first, j + knightMoves[k].second).type == EMPTY) moves.push_back(Move(i, j, i + knightMoves[k].first, j + knightMoves[k].second, piece));
      else if (board.getPiece(i + knightMoves[k].first, j + knightMoves[k].second).colour != piece.colour) moves.push_back(Move(i, j, i + knightMoves[k].first, j + knightMoves[k].second, piece, board.getPiece(i + knightMoves[k].first, j + knightMoves[k].second)));
    }
  }
}

void generateRookMoves(Board& board, int i, int j, vector<Move>& moves) {}

void generateQueenMoves(Board& board, int i, int j, vector<Move>& moves) {}

void generateKingMoves(Board& board, int i, int j, vector<Move>& moves) {}

vector<Move> generateMoves(Board& board, bool whiteToMove) {
  vector<Move> moves;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Piece piece = board.getPiece(i, j);
      if ((piece.colour == WHITE && !whiteToMove) || (piece.colour == BLACK && whiteToMove) || piece.colour == NONE) continue;

      switch (piece.type) {
        case PAWN:
          generatePawnMoves(board, i, j, moves);
          break;
        case BISHOP:
          generateBishopMoves(board, i, j, moves);
          break;
        case KNIGHT:
          generateKnightMoves(board, i, j, moves);
          break;
        case ROOK:
          generateRookMoves(board, i, j, moves);
        case QUEEN:
          generateQueenMoves(board, i, j, moves);
        case KING:
          generateKingMoves(board, i, j, moves);
        default: break;
      }
    }
  }
  
  return moves;
}

void printMoves(std::vector<Move>& moves) {
  string pieceToString[7] = {"", "", "B", "N", "R", "Q", "K"};
  bool first = true;

  for (Move& m : moves) {
    if (!first) cout << ", ";
    else first = false;

    string output;
    output += pieceToString[m.movedPiece.type];
    output += 'a' + m.fCol;
    output += to_string(8 - m.fRow);
    output += 'a' + m.tCol;
    output += to_string(8 - m.tRow);

    cout << output;
  }
  cout << endl;
}
