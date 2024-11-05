#include "Chess.h"
#include "Board.h"
#include "TopMoves.h"
#include "CustomExceptions.h"
#include <string>

int main()
{
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess a(board);
    Board game(board);
    topMoves(a,game,2);
    int codeResponse = 0;
    string res = a.getInput();
    while (res != "exit")
    {
        {
            int srcRow = res[0] - 'a';
            int srcCol = res[1] - '1';
            int destRow = res[2] - 'a';
            int destCol = res[3] - '1';
            try {
                codeResponse = game.movePiece(srcRow, srcCol, destRow, destCol);
                a.setCodeResponse(codeResponse);
                switch (codeResponse) {
                    case Board::NO_PIECE_AT_SOURCE:
                        throw InvalidMoveException("There is no piece at the source.");
                    case Board::SOURCE_PIECE_BELONGS_TO_OPPONENT:
                        throw InvalidMoveException("The piece at the source is your opponent's.");
                    case Board::DESTINATION_HAS_SAME_PLAYER_PIECE:
                        throw InvalidMoveException("There is one of your pieces at the destination.");
                    case Board::ILLEGAL_MOVEMENT:
                        throw InvalidMoveException("Illegal movement of that piece.");
                    case Board::MOVE_CAUSES_SELF_CHECK:
                        throw InvalidMoveException("This movement will cause self-check.");
                }
            }
            catch (const InvalidMoveException &e) {
                std::cerr << "Illegal move: " << e.what() << std::endl;
            }
            catch (const OutOfBoundsException &e) {
                std::cerr << "Illegal move: " << e.what() << std::endl;
            }
            if (codeResponse == 42 || codeResponse == 41 || codeResponse == 43) {
                game.switchTurn();
            }
        }
        topMoves(a,game,2);
        res = a.getInput();
    }
    cout << endl << "Exiting " << endl;
    return 0;
}