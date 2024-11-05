#include "MoveSuggester.h"

MoveSuggester::MoveSuggester(size_t maxSize, size_t printSize, int depth)
        : moveQueue(maxSize, printSize), depth(depth) {}


void MoveSuggester::suggestMoves(Board& board, Color turn) {
    moveQueue = PriorityQueue<Move>(moveQueue.getMaxSize(), moveQueue.getPrintSize());
    for (int srcRow = 0; srcRow < 8; ++srcRow) {
        for (int srcCol = 0; srcCol < 8; ++srcCol) {
            Piece* piece = board.getPiece(srcRow, srcCol);
            if (piece != nullptr && piece->color == turn) {
                for (int destRow = 0; destRow < 8; ++destRow) {
                    for (int destCol = 0; destCol < 8; ++destCol) {
                        if (piece->isValidMove(srcRow, srcCol, destRow, destCol, board.getBoard())) {
                            std::string moveStr = {static_cast<char>('a' + srcRow), static_cast<char>('1' + srcCol),
                                                   static_cast<char>('a' + destRow), static_cast<char>('1' + destCol)};
                            Move move(moveStr, 0);
                            move.score = computeMoveScore(board, move, turn, depth);
                            moveQueue.push(move);
                        }
                    }
                }
            }
        }
    }
}



int MoveSuggester::computeMoveScore(Board& board, Move move, Color turn, int depth) {
    return analyzeMoveWithDepth(board, move.move, depth, turn);
}

int MoveSuggester::analyzeMoveWithDepth(Board& board, const std::string& move, int depth, Color player) {
    int srcRow = move[0] - 'a';
    int srcCol = move[1] - '1';
    int destRow = move[2] - 'a';
    int destCol = move[3] - '1';

    Piece* movingPiece = board.getPiece(srcRow, srcCol);
    Piece* targetPiece = board.getPiece(destRow, destCol);
    int score = computeCaptureScore(targetPiece);
    score += computeThreatScore(board, movingPiece, destRow, destCol);
    score -= computeThreatScore(board, movingPiece, srcRow, srcCol);
    if (depth > 0) {
        std::vector<std::string> opponentMoves = listAllMoves(board, player == WHITE ? BLACK : WHITE);
        int bestOpponentScore = INT_MIN;
        for (const auto& opponentMove : opponentMoves) {
            int opponentScore = analyzeMoveWithDepth(board, opponentMove, depth - 1, player == WHITE ? BLACK : WHITE);
            if (opponentScore > bestOpponentScore) {
                bestOpponentScore = opponentScore;
            }
        }
        score -= bestOpponentScore;
    }
    if (depth > 1) {
        std::vector<std::string> playerMoves = listAllMoves(board, player);
        int bestPlayerScore = INT_MIN;
        for (const auto& playerMove : playerMoves) {
            int playerScore = analyzeMoveWithDepth(board, playerMove, depth - 2, player);
            if (playerScore > bestPlayerScore) {
                bestPlayerScore = playerScore;
            }
        }
        score += bestPlayerScore;
    }
    return score;
}

void MoveSuggester::printTopMoves(std::ostream& os) const {
    moveQueue.printTopMoves(os);
}

int MoveSuggester::assessThreat(Board& board, Piece* attacker, const Piece* target, int srcRow, int srcCol, int destRow, int destCol) const {
    if (attacker->isValidMove(srcRow, srcCol, destRow, destCol, board.getBoard())) {
        int score_attacker = determinePieceValue(attacker);
        int score_target = determinePieceValue(target);
        return score_target - score_attacker;
    }
    return 0;
}


int MoveSuggester::computeCaptureScore(Piece* piece) {
    if (piece) {
        return determinePieceValue(piece);
    }
    return 0;
}

std::vector<std::string> MoveSuggester::listAllMoves(Board& board, Color player) {
    std::vector<std::string> moves;
    for (int srcRow = 0; srcRow < 8; ++srcRow) {
        for (int srcCol = 0; srcCol < 8; ++srcCol) {
            Piece* piece = board.getPiece(srcRow, srcCol);
            if (piece && piece->color == player) {
                for (int destRow = 0; destRow < 8; ++destRow) {
                    for (int destCol = 0; destCol < 8; ++destCol) {
                        if (piece->isValidMove(srcRow, srcCol, destRow, destCol, board.getBoard())) {
                            moves.push_back({static_cast<char>('a' + srcRow), static_cast<char>('1' + srcCol), static_cast<char>('a' + destRow), static_cast<char>('1' + destCol)});
                        }
                    }
                }
            }
        }
    }
    return moves;
}

int MoveSuggester::computeThreatScore(Board& board, Piece* movingPiece, int destRow, int destCol) {
    int score = 0;
    for (int srcRow = 0; srcRow < 8; ++srcRow) {
        for (int srcCol = 0; srcCol < 8; ++srcCol) {
            Piece* opponent = board.getPiece(srcRow, srcCol);
            if (opponent && opponent->color != movingPiece->color) {
                score += assessThreat(board, opponent, movingPiece, srcRow, srcCol, destRow, destCol);
                score += assessThreat(board, movingPiece, opponent, destRow, destCol, srcRow, srcCol);
            }
        }
    }
    return score;
}

int MoveSuggester::determinePieceValue(const Piece* piece) const {
    if (piece == nullptr) return 0;
    switch (piece->symbol) {
        case 'P': case 'p': return 1;
        case 'N': case 'n': return 2;
        case 'B': case 'b': return 3;
        case 'R': case 'r': return 5;
        case 'Q': case 'q': return 9;
        case 'K': case 'k': return 100;
        default: return 0;
    }
}