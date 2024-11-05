#pragma once

/**
 * @enum Color
 * @brief Represents the color of a chess piece.
 */
enum Color { WHITE, BLACK, NONE };

/**
 * @enum Symbol
 * @brief Represents the symbol of a chess piece.
 */
enum Symbol {
    EMPTY = '#',
    WHITE_ROOK = 'R',
    BLACK_ROOK = 'r',
    WHITE_KING = 'K',
    BLACK_KING = 'k',
    WHITE_BISHOP = 'B',
    BLACK_BISHOP = 'b',
    WHITE_QUEEN = 'Q',
    BLACK_QUEEN = 'q',
    WHITE_KNIGHT = 'N',
    BLACK_KNIGHT = 'n',
    WHITE_PAWN = 'P',
    BLACK_PAWN = 'p'
};

/**
 * @class Piece
 * @brief Represents a generic chess piece.
 */
class Piece {
public:
    Color color;
    char symbol;

    /**
     * @brief Constructs a Piece with the specified color and symbol.
     * @param c Color of the piece.
     * @param s Symbol of the piece.
     */
    Piece(Color c, char s) : color(c), symbol(s) {}

    /**
     * @brief Checks if the move is valid for the piece.
     * @param srcRow Source row.
     * @param srcCol Source column.
     * @param destRow Destination row.
     * @param destCol Destination column.
     * @param board Current state of the board.
     * @return True if the move is valid, otherwise false.
     */
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, Piece* board[8][8]) = 0;

    /**
     * @brief Virtual destructor for Piece.
     */
    virtual ~Piece() {}
};
