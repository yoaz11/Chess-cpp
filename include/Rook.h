#pragma once
#include "Piece.h"

/**
 * @class Rook
 * @brief Represents a Rook chess piece.
 */
class Rook : public Piece {
public:

    /**
     * @brief Constructs a Rook piece with the specified color.
     * @param c Color of the Rook.
     */
    Rook(Color c);

    /**
     * @brief Checks if the move is valid for a Rook.
     * @param srcRow Source row.
     * @param srcCol Source column.
     * @param destRow Destination row.
     * @param destCol Destination column.
     * @param board Current state of the board.
     * @return True if the move is valid, otherwise false.
     */
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) override;
};
