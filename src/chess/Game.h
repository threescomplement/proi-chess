#ifndef CHESS_GAME_H
#define CHESS_GAME_H


#include <vector>
#include <string>

class Board;
class Move;
class Player;
class Piece;
class Position;
class King;
class Pawn;
class Move;

class Game {
private:
    Board *board;
    Player *whitePlayer;
    Player *blackPlayer;
    Player *currentPlayer;
    std::vector<Move> moveHistory;

    bool canWhiteKingsideCastle;
    bool canWhiteQueensideCastle;
    bool canBlackKingsideCastle;
    bool canBlackQueensideCastle;
    Position *enPassantTargetPosition;
    int halfmoveClock;
    int fullmoveNumber;

    Game(Board *board, Player *whitePlayer, Player *blackPlayer, Player *currentPlayer, bool canWhiteKingsideCastle,
         bool canWhiteQueensideCastle, bool canBlackKingsideCastle, bool canBlackQueensideCastle,
         Position *enPassantTarget, int halfmoveClock, int fullmoveNumber);

private:

    std::string castlingAvailabilityFEN() const;

    void refreshEnPassant();

    /**
     * If king move, disable castling in both directions for moving player. If rook move, disable castling
     * in its direction. If move is a rook capture and the rook has not moved yet, disable possibility of castling
     * in its direction.
     **/
    void refreshCastlingPossibilites(const Move &move);
    void refreshCastlingAfterRookCapture(const Piece *takenRook);

    /**
     * Utilites for checking whether the current player can castle - whether the flags are true and
     * there are no pieces between the king and rook
     * */
    bool possibleKingsideCastlingThisRound() const;
    bool possibleQueensideCastlingThisRound() const;
    bool noPiecesBetweenKingAndRook(const Piece* king, const Piece* rook) const;

    /**
     *Generate a move object for a castle in a given direction based on the currentPlayer parameter
     * */
    Move generateKingSideCastle() const;
    Move generateQueenSideCastle() const;

public:
    Game(std::string whiteName = "Player 1", std::string blackName = "Player 2");

    ~Game();

    Board *getBoard() const;

    Piece *getPiece(Position position) const;

    Player *getCurrentPlayer();

    std::vector<Move> &getMoveHistory();

    std::string toFEN() const;

    Player *getWhitePlayer() const;

    Player *getBlackPlayer() const;

    Player *getCurrentPlayer() const;

    void makeMove(Move move);

    Game afterMove(Move move) const;

    /**
     * All possible moves from a field during current turn.
     * */
    std::vector<Move> getMovesFrom(Position position) const;

    /**
     * All possible moves from a field not taking the current turn into account - if there is a piece on it, it returns
     * its moves.
     * */
    std::vector<Move> getAllMovesFrom(Position position) const;

    /**
     * All possible moves for a player not taking the current turn into account.
     * Like getAllMovesFrom for all pieces in one vector.
     * */
    std::vector<Move> getAllPlayerMoves(Player &player) const;

    bool isMate() const;


    /**
     * Get the pawn threatened by en passant based on enPassantTargetLocation
     * @throws std::bad_cast if the piece is not a pawn or there is no piece
     */
    Pawn *getEnPassantTargetPiece() const;

    static Game fromFEN(const std::string &fen);
};

std::vector<std::string> split(const std::string &txt, char ch);


#endif //CHESS_GAME_H
