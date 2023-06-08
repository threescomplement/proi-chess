
#ifndef CHESS_GAMEHANDLER_H
#define CHESS_GAMEHANDLER_H

#include <vector>
#include "ClickableLabel.h"
#include "Game.h"
#include "pieces/PieceType.h"
#include "Move.h"
#include "GameField.h"
#include "Color.h"
#include "../bot/StockfishBot.h"
#include "Color.h"
#include "Position.h"
#include "GameOver.h"


class GameHandler {

private:
    Game *game;
    std::vector<Move> validMoves;
    bool botGame;
    ChessBot *stockfishBot;
    Color botColor;


public:
    GameHandler();

    explicit GameHandler(Game *game, bool isBotgame = false, Color botColor = Color::BLACK);

    ~GameHandler() noexcept;

    Game *getGame() const;

    const std::vector<Move> &getValidMoves() const;

    void clearMoves();

    const std::vector<Move> &loadMovesFromPosition(Position position);

    Color getCurrentPlayerColor();

    void setBotDepth(int depth);

    Piece *getPiece(Position position);

    /**
     * check whether a field is the endpoint of one of the moves that are currenly
     * being considered
     *
     * @param position - the ending position of the desired move
     * @return the move with an endpoint at the given field, or nullptr if such a move is not found
     **/
    Move *findMoveTo(const Position position);

    void makeMove(Move const *move);

    void newGame(bool botGame, Color bot_color = Color::BLACK,
                 std::string const &fenNotation =
                 "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");


    void handleBotMove();

    void undo();

    void redo();

    GameOver isTerminalState();

    std::string getGameFen();

    bool isStalemate();

    bool isCheck(Color kingColor);

    bool isMate();

    bool fieldBelongsToCurrent(Position position);
};


#endif //CHESS_GAMEHANDLER_H
