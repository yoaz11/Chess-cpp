#include "Knight.h"
#include <cmath>

Knight::Knight(Color c) : Piece(c, c == WHITE ? 'N' : 'n') {}

bool Knight::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    int rowDiff = abs(srcRow - destRow);
    int colDiff = abs(srcCol - destCol);
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        if (board[destRow][destCol] == nullptr || board[destRow][destCol]->color != this->color) {
            return true;
        }
    }
    return false;
}
