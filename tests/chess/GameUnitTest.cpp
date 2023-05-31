#include "gtest/gtest.h"
#include "../../src/chess/Game.h"
#include "../../src/chess/Player.h"
#include "../../src/chess/Move.h"
#include "Board.h"
#include "ChessExceptions.h"
#include "common.h"

using namespace ChessUnitTestCommon;

namespace GameUnitTest {
    TEST(Game, newGameConstructor) {
        auto game = Game();

        ASSERT_EQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", game.getBoard()->toFEN());
        ASSERT_EQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", game.toFEN());

        ASSERT_EQ(16, game.getWhitePlayer()->getPieces().size());
        ASSERT_EQ(16, game.getBlackPlayer()->getPieces().size());
        ASSERT_TRUE(in(game.getWhitePlayer()->getPieces(), game.getBoard()->getWhiteKing()));
        ASSERT_TRUE(in(game.getBlackPlayer()->getPieces(), game.getBoard()->getBlackKing()));

        ASSERT_EQ(0, game.getMoveHistory().size());
    }

    TEST(Game, makeMoveNoCapture) {
        auto game = Game();
        auto pawn = game.getPiece(pos("e2"));
        auto move = Move(pos("e2"), pos("e4"), pawn);
        game.makeMove(move);

        ASSERT_EQ("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1", game.toFEN());
    }

    TEST(Game, makeMoveCapture) {
        auto game = Game::fromFEN("rnbqkbnr/pppp1pp1/8/4p2p/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq h6 0 3");
        auto capturedPawn = game.getPiece(pos("e5"));
        auto move = Move(pos("f3"), pos("e5"), game.getPiece(pos("f3")), capturedPawn);
        game.makeMove(move);
        auto blackPieces = game.getBlackPlayer()->getPieces();
        auto whitePieces = game.getWhitePlayer()->getPieces();

        ASSERT_EQ("rnbqkbnr/pppp1pp1/8/4N2p/4P3/8/PPPP1PPP/RNBQKB1R b KQkq - 0 3", game.toFEN());
        ASSERT_EQ(15, blackPieces.size());
        ASSERT_EQ(16, whitePieces.size());
        ASSERT_EQ(32, game.getBoard()->getAllPieces().size());
        ASSERT_FALSE(in(blackPieces, capturedPawn));
        ASSERT_TRUE(in(game.getBoard()->getAllPieces(), capturedPawn));
        ASSERT_THROW(capturedPawn->getPosition(), PieceNotOnBoardException);
    }

    TEST(Game, makeMoveCaptureFriendly) {
        auto game = Game::fromFEN("rnbqkbnr/ppp1pppp/8/3p4/2P5/1P6/P2PPPPP/RNBQKBNR w KQkq - 0 1");

        std::vector<Move> legalMoves = game.getMovesFrom(pos("b3"));
        ASSERT_EQ(legalMoves.size(), 1);
        Move onlyMove = legalMoves[0];
        Position expected_goal = pos("b4");
        ASSERT_EQ(onlyMove.getTo().getRow(), expected_goal.getRow());
        ASSERT_EQ(onlyMove.getTo().getCol(), expected_goal.getCol());



    }

    TEST(Game, fromFENStartingGame) {
        auto game = Game::fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        auto newGame = Game();
        ASSERT_EQ(newGame.toFEN(), game.toFEN());
        ASSERT_EQ(16, game.getWhitePlayer()->getPieces().size());
        ASSERT_EQ(16, game.getBlackPlayer()->getPieces().size());
    }

    TEST(Game, fromFENAfterMoves) {
        auto fenGame = Game::fromFEN("rnbqkbnr/pppp1ppp/8/4p3/4P3/7N/PPPP1PPP/RNBQKB1R b KQkq - 1 2");

        auto game = Game();
        game.makeMove(Move(pos("e2"), pos("e4"), game.getPiece(pos("e2"))));
        game.makeMove(Move(pos("e7"), pos("e5"), game.getPiece(pos("e7"))));
        game.makeMove(Move(pos("g1"), pos("h3"), game.getPiece(pos("g1"))));

        ASSERT_EQ(game.toFEN(), fenGame.toFEN());
        ASSERT_EQ(16, game.getWhitePlayer()->getPieces().size());
        ASSERT_EQ(16, game.getBlackPlayer()->getPieces().size());
    }

    TEST(Game, getMovesFromEmpty) {
        auto game = Game::fromFEN("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2");
        auto moves = game.getMovesFrom(pos("c4"));
        ASSERT_EQ(0, moves.size());
    }

    TEST(Game, getMovesFromNoAvailable) {
        auto game = Game::fromFEN("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2");
        auto moves = game.getMovesFrom(pos("e4"));
        ASSERT_EQ(0, moves.size());
    }

    TEST(Game, getMovesMultipleAvailable) {
        auto game = Game::fromFEN("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2");
        auto moves = game.getMovesFrom(pos("g1"));
        std::vector<Move> expected = {
                Move(pos("g1"), pos("e2"), game.getPiece(pos("g1"))),
                Move(pos("g1"), pos("f3"), game.getPiece(pos("g1"))),
                Move(pos("g1"), pos("h3"), game.getPiece(pos("g1"))),
        };
        ASSERT_TRUE(isPermutation(expected, moves));
    }

    TEST(Game, getMovesFromIncludesCapture) {
        auto game = Game::fromFEN("rnbqkbnr/pppp1pp1/8/4p2p/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq h6 0 3");
        auto moves = game.getMovesFrom(pos("f3"));
        std::vector<Move> expected = {
                Move(pos("f3"), pos("g1"), game.getPiece(pos("f3"))),
                Move(pos("f3"), pos("d4"), game.getPiece(pos("f3"))),
                Move(pos("f3"), pos("e5"), game.getPiece(pos("f3")), game.getPiece(pos("e5"))),
                Move(pos("f3"), pos("g5"), game.getPiece(pos("f3"))),
                Move(pos("f3"), pos("h4"), game.getPiece(pos("f3"))),
        };
        ASSERT_TRUE(isPermutation(expected, moves));
    }


    TEST(Game, fromFENCastling) {
        FAIL();
    }

    TEST(Game, fromFENInvalidHalfmoveClock) {
        FAIL();
    }

    TEST(Game, fromFEN) {
        FAIL();
    }
}