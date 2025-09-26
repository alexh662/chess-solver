#include <iostream>
#include "minimax.h"
#include <vector>

using namespace std;

void generatePawnMoves(Board& board, int i, int j, vector<Move>& moves) {
  Piece piece = board.getPiece(i, j);
  int direction = 1;
  if (piece.colour == WHITE) direction = -1;

  if ((direction == 1 && i + 1 < 8) || (direction == -1 && i - 1 > 0)) {
    for (int k = -1; k <= 1; k++) {
      if (j + k > 0 && j + k < 8) {
        if (k != 0) {
          if ((board.getPiece(i + direction, j + k).colour == WHITE && piece.colour == BLACK) || (board.getPiece(i + direction, j + k).colour == BLACK && piece.colour == WHITE)) {
            if ((direction == 1 && i == 1) || (direction == -1 && i == 6)) for (int i = 2; i <= 5; i++) {
              Piece promo = Piece(static_cast<PieceType>(i), piece.colour);
              moves.push_back(Move(i, j, i + direction, j + k, piece, board.getPiece(i + direction, j + k), promo));
            }
            moves.push_back(Move(i, j, i + direction, j + k, piece, board.getPiece(i + direction, j + k)));

          } else if (board.enPassant && board.enPassantCords.first == i + direction && board.enPassantCords.second == j + k) moves.push_back(Move(i, j, i + direction, j + k, piece, board.getPiece(i + direction, j + k)));
        } else if (board.getPiece(i + direction, j).type == EMPTY) {
          if ((direction == 1 && i == 1) || (direction == -1 && i == 6)) for (int i = 2; i <= 5; i++) {
            Piece promo = Piece(static_cast<PieceType>(i), piece.colour);
            moves.push_back(Move(i, j, i + direction, j, piece, board.getPiece(i + direction, j + k), promo));
          }
          moves.push_back(Move(i, j, i + direction, j, piece, board.getPiece(i + direction, j + k)));

          if (piece.colour == WHITE && i == 6) moves.push_back(Move(i, j, i - 2, j, piece, board.getPiece(i + direction, j + k)));
          else if (piece.colour == BLACK && i == 1) moves.push_back(Move(i, j, i + 2, j, piece, board.getPiece(i + direction, j + k)));
        }
      }
    }
  }
}

void generateBishopMoves(Board& board, int i, int j, vector<Move>& moves) {}

void generateKnightMoves(Board& board, int i, int j, vector<Move>& moves) {}

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

Move bestMove(Board& board, int depth, bool whiteToMove);

int minimax(Board& board, int depth, bool whiteToMove, bool maximizingPlayer) {
  if (depth == 0) return evaluateBoard(board);
}
