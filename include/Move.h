#include <string>
#include <iostream>

/**
 * @struct Move
 * @brief Represents a move in chess.
 */
struct Move {
    std::string move;
    int score;

    /**
     * @brief Constructs a Move with the specified notation and score.
     * @param m The move in algebraic notation.
     * @param s The score of the move.
     */
    Move(const std::string& m, int s) : move(m), score(s) {}

    /**
     * @brief Compares the scores of two moves.
     * @param other The move to compare with.
     * @return True if this move has a lower score than the other move.
     */
    bool operator<(const Move& other) const {
        return score < other.score;
    }

    /**
     * @brief Compares the scores of two moves.
     * @param other The move to compare with.
     * @return True if this move has a higher score than the other move.
     */
    bool operator>(const Move& other) const {
        return score > other.score;
    }

    /**
     * @brief Outputs the move notation to the given stream.
     * @param os The output stream.
     * @param m The move to output.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Move& m) {
        os << m.move;
        return os;
    }
};