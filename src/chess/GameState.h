#ifndef CHESS_GAMESTATE_H
#define CHESS_GAMESTATE_H


class Position;
class Move;
class Player;
class Pawn;
class Piece;
class Game;

struct GameState {
private:
    void updateFullmoveNumber();

    void updateHalfmoveClock(const Move &move);

    /**
     * If king move, disable castling in both directions for moving player. If rook move, disable castling
     * in its direction. If move is a rook capture and the rook has not moved yet, disable possibility of castling
     * in its direction.
     **/
    void updateCastling(const Move &move);

    void updateCastlingAfterRookCapture(const Piece *capturedRook);

    void updateEnPassantTarget(Pawn *oldEnPassantTarget);

public:
    Player *currentPlayer;
    bool canWhiteKingsideCastle;
    bool canWhiteQueensideCastle;
    bool canBlackKingsideCastle;
    bool canBlackQueensideCastle;
    Position *enPassantTargetPosition;
    int halfmoveClock;
    int fullmoveNumber;

    GameState();

    GameState(Player *currentPlayer, bool canWhiteKingsideCastle, bool canWhiteQueensideCastle,
              bool canBlackKingsideCastle, bool canBlackQueensideCastle, Position *enPassantTargetPosition,
              int halfmoveClock, int fullmoveNumber);

    void update(const Move &move, Pawn *oldEnPassantTarget);

    GameState copy(const Game &original, const Game &copied) const;

};

#endif //CHESS_GAMESTATE_H
