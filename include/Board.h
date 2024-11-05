#pragma once
#include "Piece.h"
#include <string>
using std::string;

/**
 * @class Board
 * @brief Manages the state and behavior of the chessboard.
 */
class Board {
private:
    Piece* board[8][8];
    bool whiteKingMoved;
    bool blackKingMoved;
    bool whiteRookLeftMoved;
    bool whiteRookRightMoved;
    bool blackRookLeftMoved;
    bool blackRookRightMoved;
    bool whiteKingAlive;
    bool blackKingAlive;
    Color turn;

    /**
     * @brief Initializes the board with the given string representation.
     * @param boardString String representation of the board.
     */
    void initBoard(const string& boardString);


public:

    /**
     * @brief Constructs a Board with the given string representation.
     * @param boardString String representation of the board.
     */
    Board(const string& boardString);

    /**
     * @brief Destructor for Board.
     */
    ~Board();

    /**
     * @brief Moves a piece from source to destination.
     * @param srcRow Source row.
     * @param srcCol Source column.
     * @param destRow Destination row.
     * @param destCol Destination column.
     * @return Status code of the move.
     */
    int movePiece(int srcRow, int srcCol, int destRow, int destCol);

    /**
     * @brief Checks if the given player is in check.
     * @param turn Color of the player to check.
     * @return True if the player is in check, otherwise false.
     */
    bool isInCheck(Color turn);

    /**
     * @brief Checks if the path is clear for castling.
     * @param srcRow Source row of the king.
     * @param srcCol Source column of the king.
     * @param destRow Destination row of the rook.
     * @param destCol Destination column of the rook.
     * @param turn Color of the player.
     * @return True if the path is clear for castling, otherwise false.
     */
    bool isPathClearForCastling(int srcRow, int srcCol, int destRow, int destCol, Color turn);

    /**
     * @brief Checks if the given position is in check.
     * @param turn Color of the player.
     * @param row Row to check.
     * @param col Column to check.
     * @return True if the position is in check, otherwise false.
     */
    bool isInCheckPosition(Color turn, int row, int col);

    /**
     * @brief Checks if the given player is in checkmate.
     * @param turn Color of the player to check.
     * @return True if the player is in checkmate, otherwise false.
     */
    bool isCheckmate(Color turn);

    /**
     * @brief Checks if the given player has any legal moves.
     * @param turn Color of the player to check.
     * @return True if the player has legal moves, otherwise false.
     */
    bool hasLegalMove(Color turn);

    /**
     * @brief Gets the current turn.
     * @return Color of the current turn.
     */
    Color getTurn();

    /**
     * @brief Switches the turn to the other player.
     */
    void switchTurn();

    /**
     * @brief Gets the string representation of the board.
     * @return String representation of the board.
     */
    string getStringRepresentation() const;

    /**
     * @brief Gets the piece at the given position.
     * @param row Row of the piece.
     * @param col Column of the piece.
     * @return Pointer to the piece at the position.
     * @throws OutOfBoundsException if the position is out of bounds.
     */
    Piece* getPiece(int row, int col) const;

    /**
     * @brief Gets the board.
     * @return 2D array representing the board.
     */
    Piece* (&getBoard())[8][8];

    static const int NO_PIECE_AT_SOURCE = 11;
    static const int SOURCE_PIECE_BELONGS_TO_OPPONENT = 12;
    static const int DESTINATION_HAS_SAME_PLAYER_PIECE = 13;
    static const int ILLEGAL_MOVEMENT = 21;
    static const int MOVE_CAUSES_SELF_CHECK = 31;
    static const int MOVE_LEGAL_CAUSES_CHECK = 41;
    static const int MOVE_LEGAL = 42;
    static const int CASTLING_PERFORMED = 43;
    static const int CHECKMATE = 44;
};