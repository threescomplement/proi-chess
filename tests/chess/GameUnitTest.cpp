#include "gtest/gtest.h"
#include "../../src/chess/Game.h"
#include "../../src/chess/Player.h"
#include "../../src/chess/Move.h"
#include "Board.h"
#include "pieces/Pawn.h"
#include "ChessExceptions.h"
#include "common.h"
#include "Color.h"

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
        ASSERT_EQ(pos("b4"), onlyMove.getTo());
    }

    TEST(Game, makeMoveCaptureWhileEnPassant) {
        auto game = Game::fromFEN("rnbqkbnr/ppp1pppp/8/3p4/3P4/3Q4/PPP1PPPP/RNB1KBNR b KQkq - 0 2");
        Move pawnMove = Move(pos("f7"), pos("f5"), game.getPiece(pos("f7")));
        game.makeMove(pawnMove);


        Move problematic_move = Move(pos("d3"), pos("f5"), game.getPiece(pos("d3")), game.getPiece(pos("f5")) );


        std::vector<Move> legalMoves = game.getMovesFrom(pos("d3"));
        ASSERT_TRUE(std::find(legalMoves.begin(), legalMoves.end(), problematic_move) != legalMoves.end());
        game.makeMove(problematic_move);
        ASSERT_EQ(game.toFEN(), "rnbqkbnr/ppp1p1pp/8/3p1Q2/3P4/8/PPP1PPPP/RNB1KBNR b KQkq - 0 3");

        //ASSERT_EQ(pos("b4"), onlyMove.getTo());
    }

    TEST(Game, EnPassantDeleteCaptured) {
        auto game = Game::fromFEN("rnbqkbnr/ppppp1pp/5p2/1P6/8/8/P1PPPPPP/RNBQKBNR b KQkq - 0 2");
        Move pawnMove = Move(pos("a7"), pos("a5"), game.getPiece(pos("a7")));
        game.makeMove(pawnMove);


        Move enPassantTake = Move(pos("b5"), pos("a6"), game.getPiece(pos("b5")), game.getPiece(pos("a5")) );
        std::vector<Move> legalMoves = game.getMovesFrom(pos("b5"));

        ASSERT_TRUE(std::find(legalMoves.begin(), legalMoves.end(), enPassantTake) != legalMoves.end()); // is that move available
        game.makeMove(enPassantTake);
        ASSERT_EQ(game.toFEN(), "rnbqkbnr/1pppp1pp/P4p2/8/8/8/P1PPPPPP/RNBQKBNR b KQkq - 0 3");

//        ASSERT_EQ(pos("b4"), onlyMove.getTo());
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

    /**
     * 1. e4a6 2.e5d5 3.exd6 - checking the value of enPassantTargetPiece after each move and performing enPassant
     */
    TEST(Game, staticEnPassantMechanics) {
        auto game = Game();
        auto whiteEPawn = dynamic_cast<Pawn*>(game.getBoard()->getField(pos("e2"))->getPiece());
        auto blackAPawn = dynamic_cast<Pawn*>(game.getBoard()->getField(pos("a7"))->getPiece());
        auto blackDPawn = dynamic_cast<Pawn*>(game.getBoard()->getField(pos("d7"))->getPiece());

        ASSERT_EQ(game.getEnPassantTargetPiece(), nullptr);
        // e4
        game.makeMove(Move(pos("e2"), pos("e4"), whiteEPawn, nullptr));
        ASSERT_EQ(game.getEnPassantTargetPiece(), dynamic_cast<Pawn*>(whiteEPawn));
        // a6
        game.makeMove(Move(pos("a7"), pos("a6"), blackAPawn, nullptr));
        ASSERT_EQ(game.getEnPassantTargetPiece(), nullptr);

        //e5
        game.makeMove(Move(pos("e4"), pos("e5"), whiteEPawn, nullptr));
        ASSERT_EQ(game.getEnPassantTargetPiece(), nullptr);
        //d5
        game.makeMove(Move(pos("d7"), pos("d5"), blackDPawn, nullptr));
        ASSERT_EQ(game.getEnPassantTargetPiece(), blackDPawn);

        // is exd6 a valid move?
        auto moves = whiteEPawn->getMoves();
        auto exd6EnPassant = Move(pos("e5"), pos("d6"), whiteEPawn, blackDPawn);
        ASSERT_TRUE(in(moves, exd6EnPassant));
        game.makeMove(exd6EnPassant);
        ASSERT_EQ(game.getEnPassantTargetPiece(), nullptr);
    }

    TEST(Game, enforceCurrentPlayerTurn) {
        auto game = Game();
        ASSERT_EQ(game.getCurrentPlayer()->getColor(), Color::WHITE);
        ASSERT_EQ(game.getMovesFrom(pos("e7")).size(), 0);

        auto whiteEPawn = dynamic_cast<Pawn*>(game.getBoard()->getField(pos("e2"))->getPiece());
        game.makeMove(Move(pos("e2"), pos("e4"), whiteEPawn, nullptr));
        ASSERT_EQ(game.getCurrentPlayer()->getColor(), Color::BLACK);
        ASSERT_EQ(game.getMovesFrom(pos("e7")).size(), 2);
    }

    TEST(Game, piecesBetweenKingAndRookCastling) {
        auto game = Game::fromFEN("rb2k2r/8/8/3B4/8/8/8/R3K1NR w KQkq - 0 1");
        auto whiteKing = game.getPiece(pos("e1"));
        auto blackKing = game.getPiece(pos("e8"));
        auto whiteKnight = game.getPiece(pos("g1"));
        auto blackBishop = game.getPiece(pos("b8"));
        auto whiteBishop = game.getPiece(pos("d5"));
        auto whiteKingsideCastle = Move(pos("e1"), pos("g1"), whiteKing, nullptr);
        auto blackKingsideCastle = Move(pos("e8"), pos("g8"), blackKing, nullptr);
        auto whiteQueensideCastle = Move(pos("e1"), pos("c1"), whiteKing, nullptr);
        auto blackQueensideCastle = Move(pos("e8"), pos("c8"), blackKing, nullptr);

        auto whiteKingMoves = game.getMovesFrom(pos("e1"));
        ASSERT_TRUE(in(whiteKingMoves, whiteQueensideCastle));
        ASSERT_FALSE(in(whiteKingMoves, whiteKingsideCastle));

        game.makeMove(Move(pos("g1"), pos("f3"), whiteKnight, nullptr));
        auto blackKingMoves = game.getMovesFrom(pos("e8"));
        ASSERT_TRUE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_FALSE(in(blackKingMoves, blackQueensideCastle));

        game.makeMove(Move(pos("b8"), pos("c7"), blackBishop, nullptr));
        whiteKingMoves = game.getMovesFrom(pos("e1"));
        ASSERT_TRUE(in(whiteKingMoves, whiteQueensideCastle));
        ASSERT_TRUE(in(whiteKingMoves, whiteKingsideCastle));

        game.makeMove(Move(pos("d5"), pos("g8"), whiteBishop, nullptr));
        blackKingMoves = game.getMovesFrom(pos("e8"));
        ASSERT_FALSE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_TRUE(in(blackKingMoves, blackQueensideCastle));

        game.makeMove(Move(pos("c7"), pos("b6"), blackBishop, nullptr));
        game.makeMove(Move(pos("g8"), pos("e6"), whiteBishop, nullptr));

        blackKingMoves = game.getMovesFrom(pos("e8"));
        ASSERT_TRUE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_TRUE(in(blackKingMoves, blackQueensideCastle));
    }

    TEST(Game, noCastlingAfterRookCaptured) {
        auto game = Game::fromFEN("r3k2r/8/8/3BB3/3bb3/8/8/R3K2R w KQkq - 0 1");
        auto whiteKing = game.getPiece(pos("e1"));
        auto blackKing = game.getPiece(pos("e8"));
        auto whiteKingsideRook = game.getPiece(pos("h1"));
        auto blackQueensideRook = game.getPiece(pos("a8"));
        auto whiteLightBishop = game.getPiece(pos("d5"));
        auto blackDarkBishop = game.getPiece(pos("d4"));
        auto blackLightBishop = game.getPiece(pos("e4"));
        auto whiteKingsideCastle = Move(pos("e1"), pos("g1"), whiteKing, nullptr);
        auto blackKingsideCastle = Move(pos("e8"), pos("g8"), blackKing, nullptr);
        auto whiteQueensideCastle = Move(pos("e1"), pos("c1"), whiteKing, nullptr);
        auto blackQueensideCastle = Move(pos("e8"), pos("c8"), blackKing, nullptr);

        auto whiteKingMoves = game.getMovesFrom(pos("e1"));
        ASSERT_TRUE(in(whiteKingMoves, whiteQueensideCastle));
        ASSERT_TRUE(in(whiteKingMoves, whiteKingsideCastle));

        game.makeMove(Move(pos("d5"), pos("c6"), whiteLightBishop, nullptr));
        auto blackKingMoves = game.getMovesFrom(pos("e8"));
        ASSERT_TRUE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_TRUE(in(blackKingMoves, blackQueensideCastle));

        game.makeMove(Move(pos("e4"), pos("f3"), blackLightBishop, nullptr));


        game.makeMove(Move(pos("c6"), pos("a8"), whiteLightBishop, blackQueensideRook));
        blackKingMoves = game.getMovesFrom(pos("e8"));
        ASSERT_TRUE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_FALSE(in(blackKingMoves, blackQueensideCastle));

        game.makeMove(Move(pos("f3"), pos("h1"), blackDarkBishop, whiteKingsideRook));
        whiteKingMoves = game.getMovesFrom(pos("e1"));
        ASSERT_TRUE(in(whiteKingMoves, whiteQueensideCastle));
        ASSERT_FALSE(in(whiteKingMoves, whiteKingsideCastle));
    }

    TEST(Game, noCastlingAfterRookMove) {
        auto game = Game::fromFEN("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
        auto whiteKing = game.getPiece(pos("e1"));
        auto blackKing = game.getPiece(pos("e8"));
        auto whiteKingsideRook = game.getPiece(pos("h1"));
        auto whiteQueensideRook = game.getPiece(pos("a1"));
        auto blackKingsideRook = game.getPiece(pos("h8"));
        auto whiteKingsideCastle = Move(pos("e1"), pos("g1"), whiteKing, nullptr);
        auto blackKingsideCastle = Move(pos("e8"), pos("g8"), blackKing, nullptr);
        auto whiteQueensideCastle = Move(pos("e1"), pos("c1"), whiteKing, nullptr);
        auto blackQueensideCastle = Move(pos("e8"), pos("c8"), blackKing, nullptr);

        auto whiteKingMoves = game.getMovesFrom(pos("e1"));
        ASSERT_TRUE(in(whiteKingMoves, whiteKingsideCastle));
        ASSERT_TRUE(in(whiteKingMoves, whiteQueensideCastle));
        game.makeMove(Move(pos("a1"), pos("a2"), whiteQueensideRook, nullptr));

        auto blackKingMoves = game.getMovesFrom(pos("e8"));
        ASSERT_TRUE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_TRUE(in(blackKingMoves, blackQueensideCastle));

        game.makeMove(Move(pos("h8"), pos("h7"), blackKingsideRook, nullptr));
        whiteKingMoves = game.getMovesFrom(pos("e1"));
        ASSERT_TRUE(in(whiteKingMoves, whiteKingsideCastle));
        ASSERT_FALSE(in(whiteKingMoves, whiteQueensideCastle));

        game.makeMove(Move(pos("h1"), pos("h2"), whiteKingsideRook, nullptr));
        blackKingMoves = game.getMovesFrom(pos("e8"));
        ASSERT_FALSE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_TRUE(in(blackKingMoves, blackQueensideCastle));

    }

    TEST(Game, noCastlingAfterKingMove) {
        auto game = Game::fromFEN("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
        auto whiteKing = game.getPiece(pos("e1"));
        auto blackKing = game.getPiece(pos("e8"));
        auto whiteKingsideCastle = Move(pos("e1"), pos("g1"), whiteKing, nullptr);
        auto blackKingsideCastle = Move(pos("e8"), pos("g8"), blackKing, nullptr);
        auto whiteQueensideCastle = Move(pos("e1"), pos("c1"), whiteKing, nullptr);
        auto blackQueensideCastle = Move(pos("e8"), pos("c8"), blackKing, nullptr);


        auto whiteKingMoves = game.getMovesFrom(pos("e1"));
        ASSERT_TRUE(in(whiteKingMoves, whiteKingsideCastle));
        ASSERT_TRUE(in(whiteKingMoves, whiteQueensideCastle));
        game.makeMove(Move(pos("e1"), pos("e2"), whiteKing, nullptr));

        auto blackKingMoves = game.getMovesFrom(pos("e8"));
        ASSERT_TRUE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_TRUE(in(blackKingMoves, blackQueensideCastle));
        game.makeMove(Move(pos("e8"), pos("e7"), blackKing, nullptr));

        whiteKingMoves = game.getMovesFrom(pos("e2"));
        ASSERT_FALSE(in(whiteKingMoves, whiteKingsideCastle));
        ASSERT_FALSE(in(whiteKingMoves, whiteQueensideCastle));
        game.makeMove(Move(pos("e2"), pos("e1"), whiteKing, nullptr));

        blackKingMoves = game.getMovesFrom(pos("e7"));
        ASSERT_FALSE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_FALSE(in(blackKingMoves, blackQueensideCastle));
        game.makeMove(Move(pos("e7"), pos("e8"), blackKing, nullptr));
    }

    TEST(Game, kingsideCastlingExecution) {
        auto game = Game::fromFEN("r3k2r/4n3/8/8/8/8/8/R3K2R w KQkq - 0 1");
        auto whiteKing = game.getPiece(pos("e1"));
        auto blackKing = game.getPiece(pos("e8"));
        auto whiteKingsideRook = game.getPiece(pos("h1"));
        auto blackKingsideRook = game.getPiece(pos("h8"));
        auto whiteKingsideCastle = Move(pos("e1"), pos("g1"), whiteKing, nullptr);
        auto blackKingsideCastle = Move(pos("e8"), pos("g8"), blackKing, nullptr);

        game.makeMove(whiteKingsideCastle);
        ASSERT_EQ(whiteKing->getPosition(), pos("g1"));
        ASSERT_EQ(whiteKingsideRook->getPosition(), pos("f1"));
        ASSERT_EQ(game.getCurrentPlayer()->getColor(), Color::BLACK);

        game.makeMove(blackKingsideCastle);
        ASSERT_EQ(blackKing->getPosition(), pos("g8"));
        ASSERT_EQ(blackKingsideRook->getPosition(), pos("f8"));
        ASSERT_EQ(game.getCurrentPlayer()->getColor(), Color::WHITE);
    }

    TEST(Game, queensideCastlingExecution) {
        auto game = Game::fromFEN("r3k2r/4n3/8/8/8/8/8/R3K2R w KQkq - 0 1");
        auto whiteKing = game.getPiece(pos("e1"));
        auto blackKing = game.getPiece(pos("e8"));
        auto whiteQueensideRook = game.getPiece(pos("a1"));
        auto blackQueensideRook = game.getPiece(pos("a8"));

        auto whiteQueensideCastle = Move(pos("e1"), pos("c1"), whiteKing, nullptr);
        auto blackQueensideCastle = Move(pos("e8"), pos("c8"), blackKing, nullptr);

        game.makeMove(whiteQueensideCastle);
        ASSERT_EQ(whiteKing->getPosition(), pos("c1"));
        ASSERT_EQ(whiteQueensideRook->getPosition(), pos("d1"));
        ASSERT_EQ(game.getCurrentPlayer()->getColor(), Color::BLACK);

        game.makeMove(blackQueensideCastle);
        ASSERT_EQ(blackKing->getPosition(), pos("c8"));
        ASSERT_EQ(blackQueensideRook->getPosition(), pos("d8"));
        ASSERT_EQ(game.getCurrentPlayer()->getColor(), Color::WHITE);
    }

    TEST(Game, castlingBugWhenFlagTakenDownByWrongRook) {
        auto game = Game::fromFEN("4k2r/r7/8/8/8/8/7R/R3K3 w Qk - 0 1");
        auto whiteKing = game.getPiece(pos("e1"));
        auto blackKing = game.getPiece(pos("e8"));
        auto whiteKingsideRook = game.getPiece(pos("h2"));
        auto blackQueensideRook = game.getPiece(pos("a7"));

        auto whiteKingsideCastle = Move(pos("e1"), pos("g1"), whiteKing, nullptr);
        auto blackKingsideCastle = Move(pos("e8"), pos("g8"), blackKing, nullptr);
        auto whiteQueensideCastle = Move(pos("e1"), pos("c1"), whiteKing, nullptr);
        auto blackQueensideCastle = Move(pos("e8"), pos("c8"), blackKing, nullptr);


        auto whiteKingMoves = game.getMovesFrom(pos("e1"));
        ASSERT_FALSE(in(whiteKingMoves, whiteKingsideCastle));
        ASSERT_TRUE(in(whiteKingMoves, whiteQueensideCastle));

        game.makeMove(Move(pos("h2"), pos("a2"), whiteKingsideRook, nullptr));
        auto blackKingMoves = game.getMovesFrom(pos("e8"));
        ASSERT_TRUE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_FALSE(in(blackKingMoves, blackQueensideCastle));

        game.makeMove(Move(pos("a7"), pos("h7"), blackQueensideRook, nullptr));
        whiteKingMoves = game.getMovesFrom(pos("e1"));
        ASSERT_FALSE(in(whiteKingMoves, whiteKingsideCastle));
        ASSERT_TRUE(in(whiteKingMoves, whiteQueensideCastle));

        game.makeMove(Move(pos("a2"), pos("h2"), whiteKingsideRook, nullptr));
        blackKingMoves = game.getMovesFrom(pos("e8"));
        ASSERT_TRUE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_FALSE(in(blackKingMoves, blackQueensideCastle));

        game.makeMove(Move(pos("h7"), pos("a7"), blackQueensideRook, nullptr));
        whiteKingMoves = game.getMovesFrom(pos("e1"));
        ASSERT_FALSE(in(whiteKingMoves, whiteKingsideCastle));
        ASSERT_TRUE(in(whiteKingMoves, whiteQueensideCastle));

        game.makeMove(Move(pos("h2"), pos("h1"), whiteKingsideRook, nullptr));
        blackKingMoves = game.getMovesFrom(pos("e8"));
        ASSERT_TRUE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_FALSE(in(blackKingMoves, blackQueensideCastle));
    }

}