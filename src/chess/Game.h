#ifndef CHESS_GAME_H
#define CHESS_GAME_H


#include <vector>
#include <string>
#include <map>

class Board;
class Move;
class Player;
class Piece;
class Position;
class King;
class Pawn;
class Move;
enum class Color;
enum class GameOver;

class Game {
private:
    Board *board;
    Player *whitePlayer;
    Player *blackPlayer;
    Player *currentPlayer;
    std::vector<Move> moveHistory;
    std::map<std::string, int> positionCount;
    std::vector<std::string> positionHistory;

    int movesWithoutCaptureOrPawnMove;
    bool canWhiteKingsideCastle;
    bool canWhiteQueensideCastle;
    bool canBlackKingsideCastle;
    bool canBlackQueensideCastle;
    Position *enPassantTargetPosition;
    int halfmoveClock;
    int fullmoveNumber;


    void refreshEnPassant();

    bool isCastlingObscuredByOpponent(Move &move) const;

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

    bool noPiecesBetweenKingAndRook(const Piece *king, const Piece *rook) const;

    /**
     *Generate a move object for a castle in a given direction based on the currentPlayer parameter
     * */
    Move generateKingSideCastle() const;

    Move generateQueenSideCastle() const;

    /**
     * In a situation where there are 4 or less pieces on the board. Player has only a king and a knight/bishop -> he
     * does not have enough material to mate, hence draw.
     * */
    bool isDrawByInsufficientMaterial() const;
    bool isDrawByRepetition() const;
    bool isDrawByFiftyMoveRule() const;

    /**
     * Create a deep copy of the game. Child game inherits positionCount from parent.
     * */
    Game deepCopy() const;


public:
    Game(std::string whiteName = "Player 1", std::string blackName = "Player 2");

    Game(Board *board, Player *whitePlayer, Player *blackPlayer, Player *currentPlayer, bool canWhiteKingsideCastle,
         bool canWhiteQueensideCastle, bool canBlackKingsideCastle, bool canBlackQueensideCastle,
         Position *enPassantTarget, int halfmoveClock, int fullmoveNumber);

    ~Game();

    GameOver isOver() const;

    Board *getBoard() const;

    Piece *getPiece(Position position) const;

    Player *getCurrentPlayer();

    std::vector<Move> &getMoveHistory();

    Player *getWhitePlayer() const;

    Player *getBlackPlayer() const;

    Player *getCurrentPlayer() const;

    Position *getEnPassantTargetPosition() const;

    void makeMove(Move move);

    /**
     * Creates a deep copy of the board and makes a given move on it.
     * */
    Game afterMove(const Move& move) const;

    /**
     * All possible moves from a field, taking neither the current turn nor the
     * checks and pins into consideration.
     * */
    std::vector<Move> getMovesFrom(Position position) const;

    /**
     * All possible moves for a player, not taking checks, pins and turns into account. getMovesFrom for
     * all of the locations controlled by his pieces combined.
     **/
    std::vector<Move> getAllMovesForPlayer(Player *player) const;

    /**
     * All legal moves from a field. Takes checks, pins and turns into consideration.
     * */
    std::vector<Move> getLegalMovesFrom(Position position) const;

    /**
     * All possible moves for a player. getLegalMovesFrom for all of the fields controlled by his pieces combined.
     * */
    std::vector<Move> getLegalMovesForPlayer(Player *player) const;

    bool isMate() const;

    bool isStalemate() const;

    bool isCheck(Color colorOfCheckedKing) const;

    bool isFieldControlledByPlayer(const Position &pos, Color colorOfPlayer) const;

    /**
     * Get the pawn threatened by en passant based on enPassantTargetLocation
     * @throws std::bad_cast if the piece is not a pawn or there is no piece
     */
    Pawn *getEnPassantTargetPiece() const;

    bool getCanWhiteKingsideCastle() const;

    bool getCanWhiteQueensideCastle() const;

    bool getCanBlackKingsideCastle() const;

    bool getCanBlackQueensideCastle() const;

    int getHalfmoveClock() const;

    int getFullmoveNumber() const;

    std::map<std::string, int> getPositionCount() const;

    void setPositionCount(std::map<std::string, int> count);
};

std::vector<std::string> split(const std::string &txt, char ch);


#endif //CHESS_GAME_H
