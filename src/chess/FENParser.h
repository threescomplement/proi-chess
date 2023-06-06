#ifndef CHESS_FENPARSER_H
#define CHESS_FENPARSER_H

#include <string>

class Game;
class Board;

/**
 * Handle parsing from and exporting to Forsyth–Edwards Notation
 * https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 */
class FENParser {
private:
    static std::string castlingAvailability(const Game &game);

public:
    static Game parseGame(const std::string &fen);

    /**
     * Creates a board object based on the given the FEN board description (without additional info, like castling
     * rights)
     */
    static Board *parseBoard(const std::string &fen);

    static std::string toString(const Game &game);

    static std::string toString(const Board &board);
};


#endif //CHESS_FENPARSER_H
