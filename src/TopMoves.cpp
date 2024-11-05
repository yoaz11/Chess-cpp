#include "TopMoves.h"
#include "MoveSuggester.h"
#include <sstream>
#include <iostream>


void topMoves(Chess& chessGame, Board& board, int depth) {
    MoveSuggester moveSuggester(5, 3, depth);
    moveSuggester.suggestMoves(board,board.getTurn());
    std::ostringstream oss;
    oss << "Recommended Moves: " << std::endl;
    moveSuggester.printTopMoves(oss);
    chessGame.updateMoves(oss.str());
}