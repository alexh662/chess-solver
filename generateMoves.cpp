#include <iostream>
#include <vector>
#include <utility>
#include "generateMoves.h"

using namespace std;

void addMove(Board& board, vector<Move>& moves, Move move) {
  board.makeMove(move);
  Colour colour = move.movedPiece.colour;
  if (colour == WHITE && !inCheck(board, board.whiteKingCords.first, board.whiteKingCords.second)) moves.push_back(move);
  if (colour == BLACK && !inCheck(board, board.blackKingCords.first, board.blackKingCords.second)) moves.push_back(move);
  board.undoMove(move);
}

bool inCheck(Board& board, int i, int j) {
  Piece piece = board.getPiece(i, j);
  
  // check pawns
  int direction = -1;
  if (piece.colour == WHITE) direction = 1;
  if ((i + direction >= 0 && i + direction < 8 && j + 1 < 8) && (board.getPiece(i + direction, j + 1).colour != piece.colour && board.getPiece(i + direction, j + 1).type == PAWN)) return true;
  if ((i + direction >= 0 && i + direction < 8 && j - 1 >= 0) && (board.getPiece(i + direction, j - 1).colour != piece.colour && board.getPiece(i + direction, j - 1).type == PAWN)) return true;

  // check bishops and queens
  for (int dy = -1; dy <= 1; dy += 2) {
    for (int dx = -1; dx <= 1; dx += 2) {
      for (int m = 1; i + dy*m >= 0 && i + dy*m < 8 && j + dx*m >= 0 && j + dx*m < 8; m++) {
        if (board.getPiece(i + dy*m, j + dx*m).type != EMPTY) {
          if (board.getPiece(i + dy*m, j + dx*m).colour != piece.colour && (board.getPiece(i + dy*m, j + dx*m).type == BISHOP || board.getPiece(i + dy*m, j + dx*m).type == QUEEN)) return true;
          break;
        }
      }
    }
  }

  // check knights
  vector<pair<int, int>> knightMoves = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
  for (pair<int, int> p : knightMoves) {
    if (i + p.first >= 0 && i + p.first < 8 && j + p.second >= 0 && j + p.second < 8 && board.getPiece(i + p.first, j + p.second).colour != piece.colour && board.getPiece(i + p.first, j + p.second).type == KNIGHT) return true;
  }

  // check rooks and queens
  vector<pair<int, int>> rookMoves = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
  for (pair<int, int> p : rookMoves) {
    for (int m = 1; i + p.first*m >= 0 && i + p.first*m < 8 && j + p.second*m >= 0 && j + p.second*m < 8; m++) {
      if (board.getPiece(i + p.first*m, j + p.second*m).type != EMPTY) {
        if (board.getPiece(i + p.first*m, j + p.second*m).colour != piece.colour && (board.getPiece(i + p.first*m, j + p.second*m).type == ROOK || board.getPiece(i + p.first*m, j + p.second*m).type == QUEEN)) return true;
        break;
      }
    }
  }

  // check kings
  vector<pair<int, int>> kings = {{1, 1}, {1, 0}, {0, 1}, {1, -1}, {0, -1}, {-1, 0}, {-1, 1}, {-1, -1}};
  for (pair<int, int> p : kings) {
    if (i + p.first >= 0 && i + p.first < 8 && j + p.second >= 0 && j + p.second < 8 && board.getPiece(i + p.first, j + p.second).colour != piece.colour && board.getPiece(i + p.first, j + p.second).type == KING) return true;
  }

  return false;
}

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
              addMove(board, moves, Move(i, j, i + direction, j + k, piece, board.getPiece(i + direction, j + k), promo));
            }
            addMove(board, moves, Move(i, j, i + direction, j + k, piece, board.getPiece(i + direction, j + k)));
          } else if (board.enPassant && board.enPassantCords.first == i + direction && board.enPassantCords.second == j + k) addMove(board, moves, Move(i, j, i + direction, j + k, piece, board.getPiece(i, j + k)));
        } else if (board.getPiece(i + direction, j).type == EMPTY) {
          if ((direction == 1 && i + direction == 7) || (direction == -1 && i + direction == 0)) for (int p = 2; p <= 5; p++) {
            Piece promo = Piece(static_cast<PieceType>(p), piece.colour);
            addMove(board, moves, Move(i, j, i + direction, j, piece, Piece(), promo));
          }
          addMove(board, moves, Move(i, j, i + direction, j, piece));

          if (piece.colour == WHITE && i == 6 && board.getPiece(i - 2, j).type == EMPTY) addMove(board, moves, Move(i, j, i - 2, j, piece));
          else if (piece.colour == BLACK && i == 1 && board.getPiece(i + 2, j).type == EMPTY) addMove(board, moves, Move(i, j, i + 2, j, piece));
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
          if (board.getPiece(i + k*m, j + l*m).colour != piece.colour) addMove(board, moves, Move(i, j, i + k*m, j + l*m, piece, board.getPiece(i + k*m, j + l*m)));
        } else addMove(board, moves, Move(i, j, i + k*m, j + l*m, piece));
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
      if (board.getPiece(i + knightMoves[k].first, j + knightMoves[k].second).type == EMPTY) addMove(board, moves, Move(i, j, i + knightMoves[k].first, j + knightMoves[k].second, piece));
      else if (board.getPiece(i + knightMoves[k].first, j + knightMoves[k].second).colour != piece.colour) addMove(board, moves, Move(i, j, i + knightMoves[k].first, j + knightMoves[k].second, piece, board.getPiece(i + knightMoves[k].first, j + knightMoves[k].second)));
    }
  }
}

void generateRookMoves(Board& board, int i, int j, vector<Move>& moves) {
  Piece piece = board.getPiece(i, j);
  vector<pair<int, int>> rookMoves = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
  
  for (pair<int, int> p : rookMoves) {
    int m = 1;
    bool end = false;
    while (i + p.first*m >= 0 && i + p.first*m < 8 && j + p.second*m >= 0 && j + p.second*m < 8 && !end) {
      if (board.getPiece(i + p.first*m, j + p.second*m).type != EMPTY) {
        end = true;
        if (board.getPiece(i + p.first*m, j + p.second*m).colour != piece.colour) addMove(board, moves, Move(i, j, i + p.first*m, j + p.second*m, piece, board.getPiece(i + p.first*m, j + p.second*m)));
      } else addMove(board, moves, Move(i, j, i + p.first*m, j + p.second*m, piece));
      m++;
    }
  }
}

void generateQueenMoves(Board& board, int i, int j, vector<Move>& moves) {
  generateBishopMoves(board, i, j, moves);
  generateRookMoves(board, i, j, moves);
}

void generateKingMoves(Board& board, int i, int j, vector<Move>& moves) {
  Piece piece = board.getPiece(i, j);
  vector<pair<int, int>> kingMoves = {{1, 1}, {1, 0}, {0, 1}, {1, -1}, {0, -1}, {-1, 0}, {-1, 1}, {-1, -1}};

  for (pair<int, int> p : kingMoves) {
    if (i + p.first >= 0 && i + p.first < 8 && j + p.second >= 0 && j + p.second < 8) {
      Piece capturedPiece = board.getPiece(i + p.first, j + p.second);
      if (capturedPiece.colour != piece.colour) {
        addMove(board, moves, Move(i, j, i + p.first, j + p.second, piece, capturedPiece));
      }
    }
  }
}

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
          break;
        case QUEEN:
          generateQueenMoves(board, i, j, moves);
          break;
        case KING:
          generateKingMoves(board, i, j, moves);
          break;
        default: break;
      }
    }
  }
  
  return moves;
}

void printMove(Move& m) {
  string pieceToString[7] = {"", "", "B", "N", "R", "Q", "K"};
  string output;

  output += pieceToString[m.movedPiece.type];
  output += 'a' + m.fCol;
  output += to_string(8 - m.fRow);
  output += 'a' + m.tCol;
  output += to_string(8 - m.tRow);

  cout << output;
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
