#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"
#include <iostream>
#include <cmath>
#include "CustomExceptions.h"

using std::cout; using std::endl;

Board::Board(const string& boardString) : whiteKingMoved(false), blackKingMoved(false), whiteRookLeftMoved(false), whiteRookRightMoved(false), blackRookLeftMoved(false), blackRookRightMoved(false), whiteKingAlive(true), blackKingAlive(true), turn(WHITE) {
    initBoard(boardString);
}

Board::~Board() {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            delete board[i][j];
}

void Board::initBoard(const string& boardString) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr;
        }
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char pieceChar = boardString[i * 8 + j];
            switch (pieceChar) {
                case WHITE_ROOK:
                    board[i][j] = new Rook(WHITE);
                    break;
                case BLACK_ROOK:
                    board[i][j] = new Rook(BLACK);
                    break;
                case WHITE_KING:
                    board[i][j] = new King(WHITE);
                    break;
                case BLACK_KING:
                    board[i][j] = new King(BLACK);
                    break;
                case WHITE_BISHOP:
                    board[i][j] = new Bishop(WHITE);
                    break;
                case BLACK_BISHOP:
                    board[i][j] = new Bishop(BLACK);
                    break;
                case WHITE_QUEEN:
                    board[i][j] = new Queen(WHITE);
                    break;
                case BLACK_QUEEN:
                    board[i][j] = new Queen(BLACK);
                    break;
                case WHITE_KNIGHT:
                    board[i][j] = new Knight(WHITE);
                    break;
                case BLACK_KNIGHT:
                    board[i][j] = new Knight(BLACK);
                    break;
                case WHITE_PAWN:
                    board[i][j] = new Pawn(WHITE);
                    break;
                case BLACK_PAWN:
                    board[i][j] = new Pawn(BLACK);
                    break;
                default:
                    board[i][j] = nullptr;
            }
        }
    }
}

int Board::movePiece(int srcRow, int srcCol, int destRow, int destCol) {
    if (srcRow < 0 || srcRow >= 8 || srcCol < 0 || srcCol >= 8 || destRow < 0 || destRow >= 8 || destCol < 0 || destCol >= 8) {
        throw OutOfBoundsException("Move out of board boundaries.");
    }

    Piece* srcPiece = board[srcRow][srcCol];
    if (srcPiece == nullptr)
        return NO_PIECE_AT_SOURCE;
    if (srcPiece->color != turn)
        return SOURCE_PIECE_BELONGS_TO_OPPONENT;

    if (srcPiece->symbol == (turn == WHITE ? WHITE_KING : BLACK_KING)) {
        Rook* rook = dynamic_cast<Rook*>(board[destRow][destCol]);
        if (rook != nullptr && rook->color == turn) {
            if ((srcRow == 0 && srcCol == 4 && (destRow == 0 && (destCol == 0 || destCol == 7)) && !whiteKingMoved && !whiteRookLeftMoved && !whiteRookRightMoved) ||
                (srcRow == 7 && srcCol == 4 && (destRow == 7 && (destCol == 0 || destCol == 7)) && !blackKingMoved && !blackRookLeftMoved && !blackRookRightMoved)) {
                if (isPathClearForCastling(srcRow, srcCol, destRow, destCol, turn)) {
                    if (destCol == 0) {
                        board[srcRow][2] = srcPiece;
                        board[srcRow][4] = nullptr;
                        board[destRow][3] = rook;
                        board[destRow][destCol] = nullptr;
                    } else if (destCol == 7) {
                        board[srcRow][6] = srcPiece;
                        board[srcRow][4] = nullptr;
                        board[destRow][5] = rook;
                        board[destRow][destCol] = nullptr;
                    }

                    if (turn == WHITE) {
                        whiteKingMoved = true;
                        if (destCol == 0) whiteRookLeftMoved = true;
                        else whiteRookRightMoved = true;
                    } else {
                        blackKingMoved = true;
                        if (destCol == 0) blackRookLeftMoved = true;
                        else blackRookRightMoved = true;
                    }

                    return CASTLING_PERFORMED;
                }
            }
        }
    }

    if (board[destRow][destCol] != nullptr && board[destRow][destCol]->color == turn)
        return DESTINATION_HAS_SAME_PLAYER_PIECE;

    if (!srcPiece->isValidMove(srcRow, srcCol, destRow, destCol, board))
        return ILLEGAL_MOVEMENT;

    Piece* capturedPiece = board[destRow][destCol];
    board[destRow][destCol] = srcPiece;
    board[srcRow][srcCol] = nullptr;

    if (capturedPiece != nullptr) {
        if (capturedPiece->symbol == BLACK_KING) {
            blackKingAlive = false;
        } else if (capturedPiece->symbol == WHITE_KING) {
            whiteKingAlive = false;
        }
    }

    if (srcPiece->symbol == (turn == WHITE ? WHITE_KING : BLACK_KING)) {
        if (turn == WHITE) whiteKingMoved = true;
        else blackKingMoved = true;
    } else if (srcPiece->symbol == (turn == WHITE ? WHITE_ROOK : BLACK_ROOK)) {
        if (turn == WHITE) {
            if (srcRow == 0 && srcCol == 0) whiteRookLeftMoved = true;
            if (srcRow == 0 && srcCol == 7) whiteRookRightMoved = true;
        } else {
            if (srcRow == 7 && srcCol == 0) blackRookLeftMoved = true;
            if (srcRow == 7 && srcCol == 7) blackRookRightMoved = true;
        }
    }

    bool inCheck = isInCheck(turn);
    board[srcRow][srcCol] = srcPiece;
    board[destRow][destCol] = capturedPiece;
    if (inCheck) {
        return MOVE_CAUSES_SELF_CHECK;
    }

    board[destRow][destCol] = srcPiece;
    board[srcRow][srcCol] = nullptr;

    Color opponentColor = (turn == WHITE) ? BLACK : WHITE;
    if (isInCheck(opponentColor)) {
        if (isCheckmate(opponentColor)) {
            return CHECKMATE;
        }
        return MOVE_LEGAL_CAUSES_CHECK;
    }

    if (!whiteKingAlive || !blackKingAlive) {
        return CHECKMATE;
    }

    return MOVE_LEGAL;
}

bool Board::isInCheck(Color turn) {
    int kingRow = -1, kingCol = -1;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->symbol == (turn == WHITE ? WHITE_KING : BLACK_KING)) {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
        if (kingRow != -1) break;
    }
    if (kingRow == -1 || kingCol == -1) {
        throw OutOfBoundsException("Invalid state: King is missing from the board.");
    }
    return isInCheckPosition(turn, kingRow, kingCol);
}

bool Board::isPathClearForCastling(int srcRow, int srcCol, int destRow, int destCol, Color turn){
    // Check if the path between the king and the rook is clear and the king does not pass through check
    if (destCol == 0) { // Queen-side castling
        if (board[srcRow][1] == nullptr && board[srcRow][2] == nullptr && board[srcRow][3] == nullptr &&
            !isInCheck(turn) && !isInCheckPosition(turn, srcRow, 2) && !isInCheckPosition(turn, srcRow, 3)) {
            return true;
        }
    } else if (destCol == 7) { // King-side castling
        if (board[srcRow][5] == nullptr && board[srcRow][6] == nullptr &&
            !isInCheck(turn) && !isInCheckPosition(turn, srcRow, 5) && !isInCheckPosition(turn, srcRow, 6)) {
            return true;
        }
    }
    return false;
}

bool Board::isInCheckPosition(Color turn, int row, int col){
    Color opponentColor = (turn == WHITE) ? BLACK : WHITE;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->color == opponentColor) {
                if (board[i][j]->isValidMove(i, j, row, col, board)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(Color turn) {
    if (!isInCheck(turn)) return false;

    if (hasLegalMove(turn)) return false;

    return true;
}

bool Board::hasLegalMove(Color turn) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr && board[i][j]->color == turn) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        Piece* srcPiece = board[i][j];
                        Piece* destPiece = board[x][y];

                        if (srcPiece->isValidMove(i, j, x, y, board)) {
                            board[x][y] = srcPiece;
                            board[i][j] = nullptr;
                            bool inCheck = isInCheck(turn);
                            board[i][j] = srcPiece;
                            board[x][y] = destPiece;

                            if (!inCheck) return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

string Board::getStringRepresentation() const {
    string boardString;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr) {
                boardString += board[i][j]->symbol;
            } else {
                boardString += '#';
            }
        }
    }
    return boardString;
}

Piece* Board::getPiece(int row, int col) const {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
        throw OutOfBoundsException("Move out of board boundaries.");
    }
    return board[row][col];
}

Piece* (&Board::getBoard())[8][8] {
    return board;
}

Color Board::getTurn() {
    return turn;
}

void Board::switchTurn() {
    turn = (turn == WHITE) ? BLACK : WHITE;
}
