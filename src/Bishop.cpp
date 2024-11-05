#include "Bishop.h"
#include <cmath>

Bishop::Bishop(Color c) : Piece(c, c == WHITE ? 'B' : 'b') {}

bool Bishop::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    if (abs(destRow - srcRow) != abs(destCol - srcCol)) {
        return false;
    }
    int stepX = (destRow > srcRow) ? 1 : -1;
    int stepY = (destCol > srcCol) ? 1 : -1;
    int x = srcRow + stepX;
    int y = srcCol + stepY;

    while (x != destRow && y != destCol) {
        if (board[x][y] != nullptr) {
            return false;
        }
        x += stepX;
        y += stepY;
    }
    Piece* destinationPiece = board[destRow][destCol];
    if (destinationPiece != nullptr && destinationPiece->color == this->color) {
        return false;
    }
    return true;
}
