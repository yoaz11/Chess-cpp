#include "Queen.h"

Queen::Queen(Color c) : Piece(c, c == WHITE ? 'Q' : 'q') {}

bool Queen::isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) {
    Bishop bishop(color);
    Rook rook(color);

    // Use Bishop's diagonal move validation
    if (bishop.isValidMove(srcRow, srcCol, destRow, destCol, board)) {
        return true;
    }

    // Use Rook's horizontal/vertical move validation
    if (rook.isValidMove(srcRow, srcCol, destRow, destCol, board)) {
        return true;
    }

    return false;
}
