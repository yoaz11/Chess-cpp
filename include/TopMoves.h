#pragma once
#include "Chess.h"
#include "Board.h"
#include <string>

/**
 * @brief Suggests the top moves for the given chess game and board state.
 * @param chessGame Reference to the Chess game object.
 * @param board Reference to the Board object.
 * @param depth Depth of move analysis.
 */
void topMoves(Chess& chessGame, Board& board, int depth);