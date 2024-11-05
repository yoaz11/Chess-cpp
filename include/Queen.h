#pragma once
#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"

/**
 * @class Queen
 * @brief Represents a Queen chess piece.
 */
class Queen : public Piece {
public:

    /**
     * @brief Constructs a Queen piece with the specified color.
     * @param c Color of the Queen.
     */
    Queen(Color c);

    /**
     * @brief Checks if the move is valid for a Queen.
     * @param srcRow Source row.
     * @param srcCol Source column.
     * @param destRow Destination row.
     * @param destCol Destination column.
     * @param board Current state of the board.
     * @return True if the move is valid, otherwise false.
     */
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) override;
};
