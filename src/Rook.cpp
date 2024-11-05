#include <iostream>
#include "Rook.h"

Rook::Rook(Color c) : Piece(c, c == WHITE ? 'R' : 'r') {}

bool Rook::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    if (srcRow != destCol && srcCol != destCol) {
        return false;
    }
    int xDirection = (destRow - srcRow) == 0 ? 0 : (destRow - srcRow) / abs(destRow - srcRow);
    int yDirection = (destCol - srcCol) == 0 ? 0 : (destCol - srcCol) / abs(destCol - srcCol);

    int x = srcRow + xDirection;
    int y = srcCol + yDirection;

    while (x != destRow || y != destCol) {
        if (board[x][y] != nullptr) {
            return false; // Path is blocked
        }
        x += xDirection;
        y += yDirection;
    }

    Piece* destinationPiece = board[destRow][destCol];
    return destinationPiece == nullptr || destinationPiece->color != this->color;
}

