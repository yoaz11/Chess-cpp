#pragma once
#include "Piece.h"

/**
 * @class Pawn
 * @brief Represents a Pawn chess piece.
 */
class Pawn : public Piece {
public:

    /**
     * @brief Constructs a Pawn piece with the specified color.
     * @param c Color of the Pawn.
     */
    Pawn(Color c);

    /**
     * @brief Checks if the move is valid for a Pawn.
     * @param srcRow Source row.
     * @param srcCol Source column.
     * @param destRow Destination row.
     * @param destCol Destination column.
     * @param board Current state of the board.
     * @return True if the move is valid, otherwise false.
     */
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) override;
};
