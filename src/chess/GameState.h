#ifndef CHESS_GAMESTATE_H
#define CHESS_GAMESTATE_H


class Position;
class Move;
class Player;
class Pawn;
class Piece;

struct GameState {
private:
    void updateFullmoveNumber(const Move &move);

    void updateHalfmoveClock(const Move &move);

    /**
     * If king move, disable castling in both directions for moving player. If rook move, disable castling
     * in its direction. If move is a rook capture and the rook has not moved yet, disable possibility of castling
     * in its direction.
     **/
    void updateCastling(const Move &move);

    void updateCastlingAfterRookCapture(const Piece *capturedRook);

    void updateEnPassantTarget(const Move &move, Pawn *oldEnPassantTarget);

public:
    Player *currentPlayer;
    bool canWhiteKingsideCastle;
    bool canWhiteQueensideCastle;
    bool canBlackKingsideCastle;
    bool canBlackQueensideCastle;
    Position *enPassantTargetPosition;
    int halfmoveClock;
    int fullmoveNumber;


    void update(const Move &move, Pawn *oldEnPassantTarget);

};

#endif //CHESS_GAMESTATE_H
