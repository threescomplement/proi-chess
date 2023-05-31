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

    std::vector<Move> getMovesFrom(Position position) const;

    std::vector<Move> getAllPlayerMoves(Player &player) const;

    bool isMate() const;

    bool isCheck() const;

    /**
     * Get the pawn threatened by en passant based on enPassantTargetLocation
     * @throws std::bas_cast if the piece is not a pawn or there is no piece
     */
    Pawn *getEnPassantTargetPiece() const;

    static Game fromFEN(const std::string &fen);
};

std::vector<std::string> split(const std::string &txt, char ch);


#endif //CHESS_GAME_H
