#include "Pawn.h"

Pawn::Pawn(Color c) : Piece(c, c == WHITE ? 'P' : 'p') {}

bool Pawn::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    int direction = (color == WHITE) ? 1 : -1;
    int startRow = (color == WHITE) ? 1 : 6;

    // Single step forward
    if (destRow == srcRow + direction && destCol == srcCol && board[destRow][destCol] == nullptr) {
        return true;
    }

    // Double step forward from starting position
    if (srcRow == startRow && destRow == srcRow + 2 * direction && destCol == srcCol &&
        board[srcRow + direction][srcCol] == nullptr && board[destRow][destCol] == nullptr) {
        return true;
    }

    // Capture move
    if (destRow == srcRow + direction && (destCol == srcCol + 1 || destCol == srcCol - 1) &&
        board[destRow][destCol] != nullptr && board[destRow][destCol]->color != this->color) {
        return true;
    }

    return false;
}
