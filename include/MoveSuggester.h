#pragma once
#include "PriorityQueue.h"
#include "Move.h"
#include "Board.h"
#include <vector>
#include <string>
#include <iostream>

/**
 * @class MoveSuggester
 * @brief Suggests moves for a chess game.
 */
class MoveSuggester {
public:

    /**
     * @brief Constructs a MoveSuggester with the specified parameters.
     * @param maxSize Maximum size of the move queue.
     * @param printSize Number of top moves to print.
     * @param depth Depth of move analysis.
     */
    MoveSuggester(size_t maxSize, size_t printSize, int depth);

    /**
     * @brief Suggests moves for the current board state and turn.
     * @param board Current state of the board.
     * @param turn Current player's turn.
     */
    void suggestMoves(Board& board, Color turn);

    /**
     * @brief Prints the top suggested moves.
     * @param os Output stream to print the moves.
     */
    void printTopMoves(std::ostream& os) const;

private:
    int depth;
    PriorityQueue<Move> moveQueue;

    /**
     * @brief Computes the score for a given move.
     * @param board Current state of the board.
     * @param move The move to evaluate.
     * @param turn Current player's turn.
     * @param depth Depth of analysis.
     * @return The score of the move.
     */
    int computeMoveScore(Board& board, Move move, Color turn, int depth);

    /**
     * @brief Analyzes a move with the specified depth.
     * @param board Current state of the board.
     * @param move The move to analyze.
     * @param depth Depth of analysis.
     * @param player Current player's color.
     * @return The score of the move after analysis.
     */
    int analyzeMoveWithDepth(Board& board, const std::string& move, int depth, Color player);

    /**
     * @brief Determines the value of a piece.
     * @param piece The piece to evaluate.
     * @return The value of the piece.
     */
    int determinePieceValue(const Piece* piece) const;

    /**
     * @brief Computes the capture score for a piece.
     * @param targetPiece The piece to capture.
     * @return The score of the capture.
     */
    int computeCaptureScore(Piece* piece);

    /**
     * @brief Computes the threat score for a move.
     * @param board Current state of the board.
     * @param movingPiece The piece to move.
     * @param destX Destination row.
     * @param destY Destination column.
     * @return The threat score of the move.
     */
    int computeThreatScore(Board& board, Piece* movingPiece, int destRow, int destCol);

    /**
     * @brief Assesses the threat of a move.
     * @param board Current state of the board.
     * @param attacker The attacking piece.
     * @param target The target piece.
     * @param srcX Source row of the attacker.
     * @param srcY Source column of the attacker.
     * @param destX Destination row of the attacker.
     * @param destY Destination column of the attacker.
     * @return The threat score of the move.
     */
    int assessThreat(Board& board, Piece* attacker, const Piece* target, int srcRow, int srcCol, int destRow, int destCol) const;

    /**
     * @brief Lists all possible moves for the current player.
     * @param board Current state of the board.
     * @param player Current player's color.
     * @return A vector of possible moves.
     */
    std::vector<std::string> listAllMoves(Board& board, Color player);
};

