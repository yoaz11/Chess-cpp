#include "King.h"
#include <cmath>

King::King(Color c) : Piece(c, c == WHITE ? 'K' : 'k') {}


bool King::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    int rowDiff = std::abs(srcRow - destRow);
    int colDiff = std::abs(srcCol - destCol);
    if ((rowDiff <= 1 && colDiff <= 1) && (rowDiff + colDiff > 0)) {
        if (board[destRow][destCol] == nullptr || board[destRow][destCol]->color != this->color) {
            return true;
        }
    }
    return false;
}
