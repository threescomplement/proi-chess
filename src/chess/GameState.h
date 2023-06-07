#ifndef CHESS_GAMESTATE_H
#define CHESS_GAMESTATE_H


class Position;
class Move;
class Player;
class Pawn;

struct GameState {
    Player *currentPlayer;
    bool canWhiteKingsideCastle;
    bool canWhiteQueensideCastle;
    bool canBlackKingsideCastle;
    bool canBlackQueensideCastle;
    Position *enPassantTargetPosition;
    int halfmoveClock;
    int fullmoveNumber;

    void updateFullmoveNumber(const Move &move);

    void updateHalfmoveClock(const Move &move);

    void updateCastling(const Move &move);

    void updateEnPassantTarget(const Move &move, Pawn *oldEnPassantTarget);

};

#endif //CHESS_GAMESTATE_H
