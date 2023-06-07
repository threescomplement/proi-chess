#ifndef CHESS_GAMESTATE_H
#define CHESS_GAMESTATE_H

class Position;

struct GameState {
    bool canWhiteKingsideCastle;
    bool canWhiteQueensideCastle;
    bool canBlackKingsideCastle;
    bool canBlackQueensideCastle;
    Position *enPassantTargetPosition;
    int halfmoveClock;
    int fullmoveNumber;
};

#endif //CHESS_GAMESTATE_H
