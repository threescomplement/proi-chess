#include "gtest/gtest.h"
#include "Game.h"
#include "Player.h"
#include "Move.h"
#include "Board.h"
#include "pieces/Pawn.h"
#include "ChessExceptions.h"
#include "common.h"
#include "Color.h"
#include "GameOver.h"
#include "pieces/PieceType.h"

using namespace ChessUnitTestCommon;

namespace GameUnitTest {
    TEST(Game, newGameConstructor) {
        auto game = Game();

        ASSERT_EQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", fen(game.getBoard()));
        ASSERT_EQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", fen(game));

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

        ASSERT_EQ("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1", fen(game));
    }

    TEST(Game, makeMoveCapture) {
        auto game = fenGame("rnbqkbnr/pppp1pp1/8/4p2p/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq h6 0 3");
        auto capturedPawn = game.getPiece(pos("e5"));
        auto move = Move(pos("f3"), pos("e5"), game.getPiece(pos("f3")), capturedPawn);
        game.makeMove(move);
        auto blackPieces = game.getBlackPlayer()->getPieces();
        auto whitePieces = game.getWhitePlayer()->getPieces();

        ASSERT_EQ("rnbqkbnr/pppp1pp1/8/4N2p/4P3/8/PPPP1PPP/RNBQKB1R b KQkq - 0 3", fen(game));
        ASSERT_EQ(15, blackPieces.size());
        ASSERT_EQ(16, whitePieces.size());
        ASSERT_EQ(32, game.getBoard()->getAllPieces().size());
        ASSERT_FALSE(in(blackPieces, capturedPawn));
        ASSERT_TRUE(in(game.getBoard()->getAllPieces(), capturedPawn));
        ASSERT_THROW(capturedPawn->getPosition(), PieceNotOnBoardException);
    }

    TEST(Game, makeMoveCaptureFriendly) {
        auto game = fenGame("rnbqkbnr/ppp1pppp/8/3p4/2P5/1P6/P2PPPPP/RNBQKBNR w KQkq - 0 1");

        std::vector<Move> legalMoves = game.getMovesFrom(pos("b3"));
        ASSERT_EQ(legalMoves.size(), 1);
        Move onlyMove = legalMoves[0];
        ASSERT_EQ(pos("b4"), onlyMove.getTo());
    }

    TEST(Game, makeMoveCaptureWhileEnPassant) {
        auto game = fenGame("rnbqkbnr/ppp1pppp/8/3p4/3P4/3Q4/PPP1PPPP/RNB1KBNR b KQkq - 0 2");
        Move pawnMove = Move(pos("f7"), pos("f5"), game.getPiece(pos("f7")));
        game.makeMove(pawnMove);


        Move problematic_move = Move(pos("d3"), pos("f5"), game.getPiece(pos("d3")), game.getPiece(pos("f5")));


        std::vector<Move> legalMoves = game.getMovesFrom(pos("d3"));
        ASSERT_TRUE(std::find(legalMoves.begin(), legalMoves.end(), problematic_move) != legalMoves.end());
        game.makeMove(problematic_move);
        ASSERT_EQ(fen(game), "rnbqkbnr/ppp1p1pp/8/3p1Q2/3P4/8/PPP1PPPP/RNB1KBNR b KQkq - 0 3");
    }

    TEST(Game, EnPassantDeleteCaptured) {
        auto game = fenGame("rnbqkbnr/ppppp1pp/5p2/1P6/8/8/P1PPPPPP/RNBQKBNR b KQkq - 0 2");
        Move pawnMove = Move(pos("a7"), pos("a5"), game.getPiece(pos("a7")));
        game.makeMove(pawnMove);


        Move enPassantTake = Move(pos("b5"), pos("a6"), game.getPiece(pos("b5")), game.getPiece(pos("a5")));
        std::vector<Move> legalMoves = game.getMovesFrom(pos("b5"));

        ASSERT_TRUE(std::find(legalMoves.begin(), legalMoves.end(), enPassantTake) !=
                    legalMoves.end()); // is that move available
        game.makeMove(enPassantTake);
        ASSERT_EQ(fen(game), "rnbqkbnr/1pppp1pp/P4p2/8/8/8/P1PPPPPP/RNBQKBNR b KQkq - 0 3");
    }


    TEST(Game, getMovesFromEmpty) {
        auto game = fenGame("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2");
        auto moves = game.getMovesFrom(pos("c4"));
        ASSERT_EQ(0, moves.size());
    }

    TEST(Game, getMovesFromNoAvailable) {
        auto game = fenGame("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2");
        auto moves = game.getMovesFrom(pos("e4"));
        ASSERT_EQ(0, moves.size());
    }

    TEST(Game, getMovesMultipleAvailable) {
        auto game = fenGame("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2");
        auto moves = game.getMovesFrom(pos("g1"));
        std::vector<Move> expected = {
                Move(pos("g1"), pos("e2"), game.getPiece(pos("g1"))),
                Move(pos("g1"), pos("f3"), game.getPiece(pos("g1"))),
                Move(pos("g1"), pos("h3"), game.getPiece(pos("g1"))),
        };
        ASSERT_TRUE(isPermutation(expected, moves));
    }

    TEST(Game, getMovesFromIncludesCapture) {
        auto game = fenGame("rnbqkbnr/pppp1pp1/8/4p2p/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq h6 0 3");
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


    /**
     * 1. e4a6 2.e5d5 3.exd6 - checking the value of enPassantTargetPiece after each move and performing enPassant
     */
    TEST(Game, staticEnPassantMechanics) {
        auto game = Game();
        auto whiteEPawn = dynamic_cast<Pawn *>(game.getBoard()->getField(pos("e2"))->getPiece());
        auto blackAPawn = dynamic_cast<Pawn *>(game.getBoard()->getField(pos("a7"))->getPiece());
        auto blackDPawn = dynamic_cast<Pawn *>(game.getBoard()->getField(pos("d7"))->getPiece());

        ASSERT_EQ(game.getEnPassantTargetPiece(), nullptr);
        // e4
        game.makeMove(Move(pos("e2"), pos("e4"), whiteEPawn, nullptr));
        ASSERT_EQ(game.getEnPassantTargetPiece(), dynamic_cast<Pawn *>(whiteEPawn));
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
        ASSERT_EQ(game.getLegalMovesFrom(pos("e7")).size(), 0);

        auto whiteEPawn = dynamic_cast<Pawn *>(game.getBoard()->getField(pos("e2"))->getPiece());
        game.makeMove(Move(pos("e2"), pos("e4"), whiteEPawn, nullptr));
        ASSERT_EQ(game.getCurrentPlayer()->getColor(), Color::BLACK);
        ASSERT_EQ(game.getMovesFrom(pos("e7")).size(), 2);
    }

    TEST(Game, piecesBetweenKingAndRookCastling) {
        auto game = fenGame("rb2k2r/8/8/3B4/8/8/8/R3K1NR w KQkq - 0 1");
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
        auto game = fenGame("r3k2r/8/8/3BB3/3bb3/8/8/R3K2R w KQkq - 0 1");
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
        auto game = fenGame("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
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
        auto game = fenGame("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
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
        auto game = fenGame("r3k2r/4n3/8/8/8/8/8/R3K2R w KQkq - 0 1");
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
        auto game = fenGame("r3k2r/4n3/8/8/8/8/8/R3K2R w KQkq - 0 1");
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
        auto game = fenGame("4k2r/r7/8/8/8/8/7R/R3K3 w Qk - 0 1");
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

    TEST(Game, queenCheck) {
        auto game = fenGame("rnb1kbnr/ppppqppp/8/8/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1");
        ASSERT_TRUE(game.isCheck(Color::WHITE));
        ASSERT_FALSE(game.isCheck(Color::BLACK));
    }

    TEST(Game, pawnCheck) {
        auto game = fenGame("rnbqkbn1/pppppPpp/8/8/8/8/PPPPPPPP/RNBQK1NR w KQq - 0 1");
        ASSERT_TRUE(game.isCheck(Color::BLACK));
        ASSERT_FALSE(game.isCheck(Color::WHITE));
    }

    TEST(Game, rookCheck) {
        auto game = fenGame("rnbqkbn1/pppppppp/8/8/8/8/PPPPPPPP/RNBQKrNR w KQq - 0 1");
        ASSERT_TRUE(game.isCheck(Color::WHITE));
        ASSERT_FALSE(game.isCheck(Color::BLACK));
    }

    TEST(Game, bishopCheck) {
        auto game = fenGame("rnbqkbnr/pp2pppp/2Bp4/8/8/5N2/PPPPPPPP/RNBQK2R w KQkq - 0 1");
        ASSERT_FALSE(game.isCheck(Color::WHITE));
        ASSERT_TRUE(game.isCheck(Color::BLACK));
    }

    TEST(Game, knightCheck) {
        auto game2 = fenGame("rnbqkbnr/pppppppp/5N2/8/8/8/PPPPPPPP/RNBQKB1R w KQkq - 0 1");
        ASSERT_FALSE(game2.isCheck(Color::WHITE));
        ASSERT_TRUE(game2.isCheck(Color::BLACK));
    }

    TEST(Game, afterMove1) {
        auto game = fenGame("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        auto e4 = Move(pos("e2"), pos("e4"), game.getPiece(pos("e2")), nullptr);
        auto copy = game.afterMove(e4);

        ASSERT_TRUE(game.getPiece(pos("e2")) != nullptr);
        ASSERT_TRUE(game.getPiece(pos("e4")) == nullptr);

        ASSERT_TRUE(copy.getPiece(pos("e2")) == nullptr);
        ASSERT_TRUE(copy.getPiece(pos("e4")) != nullptr);
    }

    TEST(Game, afterMove2) {
        auto game = fenGame("rnbqkbnr/ppppp2p/6p1/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
        auto exf6 = Move(pos("e5"), pos("f6"), game.getPiece(pos("e5")), game.getPiece(pos("f5")));
        auto copy = game.afterMove(exf6);

        ASSERT_TRUE(game.getPiece(pos("e5")) != nullptr);
        ASSERT_TRUE(game.getPiece(pos("f5")) != nullptr);
        ASSERT_TRUE(game.getPiece(pos("f6")) == nullptr);

        ASSERT_TRUE(copy.getPiece(pos("e5")) == nullptr);
        ASSERT_TRUE(copy.getPiece(pos("f5")) == nullptr);
        ASSERT_TRUE(copy.getPiece(pos("f6")) != nullptr);
    }

    TEST(Game, availableMovesUnderCheck) {
        auto game = fenGame("k7/8/8/8/8/6b1/3PP3/3PKP2 w - - 0 1");
        auto onlyMove = Move(pos("f1"), pos("f2"), game.getPiece(pos("f1")), nullptr);
        auto movesForWhite = game.getLegalMovesForPlayer(game.getWhitePlayer());

        ASSERT_TRUE(in(movesForWhite, onlyMove));
        ASSERT_EQ(movesForWhite.size(), 1);
    }

    TEST(Game, pinnedPieceCanOnlyCapturePinner) {
        auto game = fenGame("3k4/8/8/8/8/5q2/4B3/3K4 w - - 0 1");
        auto onlyMove = Move(pos("e2"), pos("f3"), game.getPiece(pos("e2")), game.getPiece(pos("f3")));
        auto movesForWhiteBishop = game.getLegalMovesFrom(pos("e2"));

        ASSERT_TRUE(in(movesForWhiteBishop, onlyMove));
        ASSERT_EQ(movesForWhiteBishop.size(), 1);
    }

    TEST(Game, canKingMoveWhenCheckedBug) {
        auto game = fenGame("rnb1kbnr/ppp1pQpp/8/8/8/7B/PPPPPPPP/RNB1K1NR b KQkq - 0 1");
        auto captureQueen = Move(pos("e8"), pos("f7"), game.getPiece(pos("e8")), game.getPiece(pos("f7")));
        auto runFromCheck = Move(pos("e8"), pos("d8"), game.getPiece(pos("e8")), nullptr);
        auto blackMoves = game.getLegalMovesForPlayer(game.getBlackPlayer());
        ASSERT_TRUE(in(blackMoves, captureQueen));
        ASSERT_TRUE(in(blackMoves, runFromCheck));
        ASSERT_EQ(blackMoves.size(), 2);

    }

    TEST(Game, cantCastleUnderCheck) {
        auto game = fenGame("rnbqk2r/ppppQppp/3n2N1/8/8/8/PPPP1PPP/RNB1KB1R b KQkq - 0 1");
        auto onlyMove = Move(pos("d8"), pos("e7"), game.getPiece(pos("d8")), game.getPiece(pos("e7")));
        auto movesForBlack = game.getLegalMovesForPlayer(game.getBlackPlayer());

        ASSERT_TRUE(in(movesForBlack, onlyMove));
        ASSERT_EQ(movesForBlack.size(), 1);
    }

    TEST(Game, cantCastleThroughCheck) {
        auto game = fenGame("rnbqk2r/pppp2pp/3n2N1/8/8/5Q2/PPPP1PPP/RNB1KB1R b KQkq - 0 1");
        auto movesForBlackKing = game.getLegalMovesFrom(pos("e8"));
        ASSERT_TRUE(movesForBlackKing.empty());
    }

    TEST(Game, cantCastleThroughPawnsControlOfAField) {
        auto game = fenGame("rnbqkbnr/ppppppp1/8/8/8/8/PPpPPPPP/R3KBNR w KQkq - 0 1");
        auto movesForWhiteKing = game.getLegalMovesFrom(pos("e1"));
        ASSERT_TRUE(movesForWhiteKing.empty());
    }

    TEST(Game, isMate1) {
        auto game = fenGame("r1bqkbnr/pppp1Qp1/2n4p/4p3/2B1P3/8/PPPP1PPP/RNB1K1NR b KQkq - 0 1");
        ASSERT_TRUE(game.isMate());
    }

    TEST(Game, isMate2) {
        auto game = fenGame("r1bqkb1r/pppp1Qp1/2nn3p/4p3/2B1P3/8/PPPP1PPP/RNB1K1NR b KQkq - 0 1");
        ASSERT_FALSE(game.isMate());
    }

    TEST(Game, isMate3) {
        auto game = fenGame("r1b1k2r/ppppqppp/8/8/1PP2Bn1/3n1N2/1P1NPPPP/R2QKB1R w KQkq - 0 1");
        ASSERT_TRUE(game.isMate());
    }

    TEST(Game, isMate4) {
        auto game = fenGame("rnbqkbn1/pppppppp/8/8/8/8/PPPPPPPP/R3K2r w Qq - 0 1");
        auto isCheck = game.isCheck(Color::WHITE);
        auto moves = game.getLegalMovesForPlayer(game.getWhitePlayer());
        ASSERT_TRUE(game.isMate());
    }

    TEST(Game, isStalemate1) {
        auto game = fenGame("1k6/8/8/8/8/8/2q5/K7 w - - 0 1");
        ASSERT_TRUE(game.isStalemate());
    }

    TEST(Game, isStalemate2) {
        auto game = fenGame("1k6/4R3/8/8/R7/8/8/K1Q5 b - - 0 1");
        ASSERT_TRUE(game.isStalemate());
    }

    TEST(Game, promoteToRook) {
        auto game = fenGame("8/7P/3k4/8/8/8/4K3/8 w - - 0 1");
        auto whitePawn = game.getPiece(pos("h7"));
        auto promotion = Move(pos("h7"), pos("h8"), whitePawn, PieceType::ROOK);
        game.makeMove(promotion);

        ASSERT_TRUE(whitePawn->getField() == nullptr);
        ASSERT_EQ(game.getPiece(pos("h7")), nullptr);
        ASSERT_EQ(game.getPiece(pos("h8"))->getType(), PieceType::ROOK);
        ASSERT_EQ(game.getPiece(pos("h8"))->getField(), game.getBoard()->getField(pos("h8")));

    }

    TEST(Game, promoteToQueen) {
        auto game = fenGame("7r/1P6/3k4/8/8/2K5/8/8 w - - 0 1");
        auto whitePawn = game.getPiece(pos("b7"));
        auto promotion = Move(pos("b7"), pos("b8"), whitePawn, PieceType::QUEEN);
        game.makeMove(promotion);

        ASSERT_TRUE(whitePawn->getField() == nullptr);
        ASSERT_EQ(game.getPiece(pos("b7")), nullptr);
        ASSERT_EQ(game.getPiece(pos("b8"))->getType(), PieceType::QUEEN);
        ASSERT_EQ(game.getPiece(pos("b8"))->getField(), game.getBoard()->getField(pos("b8")));
    }

    TEST(Game, promoteToKnight) {
        auto game = fenGame("1r6/1P6/3k4/8/8/5K2/6p1/8 b - - 0 1");
        auto blackPawn = game.getPiece(pos("g2"));
        auto promotion = Move(pos("g2"), pos("g1"), blackPawn, PieceType::KNIGHT);
        game.makeMove(promotion);

        ASSERT_TRUE(blackPawn->getField() == nullptr);
        ASSERT_EQ(game.getPiece(pos("g2")), nullptr);
        ASSERT_EQ(game.getPiece(pos("g1"))->getType(), PieceType::KNIGHT);
        ASSERT_EQ(game.getPiece(pos("g1"))->getField(), game.getBoard()->getField(pos("g1")));
    }

    TEST(Game, promoteToBishop) {
        auto game = fenGame("8/4PK2/3k4/8/8/8/6p1/8 w - - 0 1");
        auto whitePawn = game.getPiece(pos("e7"));
        auto promotion = Move(pos("e7"), pos("e8"), whitePawn, PieceType::BISHOP);
        game.makeMove(promotion);

        ASSERT_TRUE(whitePawn->getField() == nullptr);
        ASSERT_EQ(game.getPiece(pos("e7")), nullptr);
        ASSERT_EQ(game.getPiece(pos("e8"))->getType(), PieceType::BISHOP);
        ASSERT_EQ(game.getPiece(pos("e8"))->getField(), game.getBoard()->getField(pos("e8")));
    }

    TEST(Game, promoteWithCheck) {
        auto game = fenGame("8/4P1k1/4K3/8/8/6B1/8/8 w - - 0 1");
        auto whitePawn = game.getPiece(pos("e7"));
        auto promotion = Move(pos("e7"), pos("e8"), whitePawn, PieceType::KNIGHT);
        game.makeMove(promotion);

        ASSERT_TRUE(whitePawn->getField() == nullptr);
        ASSERT_EQ(game.getPiece(pos("e7")), nullptr);
        ASSERT_EQ(game.getPiece(pos("e8"))->getType(), PieceType::KNIGHT);
        ASSERT_EQ(game.getPiece(pos("e8"))->getField(), game.getBoard()->getField(pos("e8")));
        ASSERT_TRUE(game.isCheck(Color::BLACK));
        ASSERT_FALSE(game.isMate());
    }

    TEST(Game, promoteWithMate) {
        auto game = fenGame("8/4KP1k/8/8/8/1B6/1B6/2Q5 w - - 0 1");
        auto whitePawn = game.getPiece(pos("f7"));
        auto promotion = Move(pos("f7"), pos("f8"), whitePawn, PieceType::KNIGHT);
        game.makeMove(promotion);

        ASSERT_TRUE(whitePawn->getField() == nullptr);
        ASSERT_EQ(game.getPiece(pos("f7")), nullptr);
        ASSERT_EQ(game.getPiece(pos("f8"))->getType(), PieceType::KNIGHT);
        ASSERT_EQ(game.getPiece(pos("f8"))->getField(), game.getBoard()->getField(pos("f8")));
        ASSERT_TRUE(game.isCheck(Color::BLACK));
        ASSERT_TRUE(game.isMate());

    }

    TEST(Game, promoteByTakingWithCheck) {
        auto game = fenGame("5r2/4P1k1/8/8/2K5/8/8/8 w - - 0 1");
        auto whitePawn = game.getPiece(pos("e7"));
        auto blackRook = game.getPiece(pos("f8"));
        auto promotion = Move(pos("e7"), pos("f8"), whitePawn, blackRook, PieceType::QUEEN);
        game.makeMove(promotion);

        ASSERT_TRUE(whitePawn->getField() == nullptr);
        ASSERT_EQ(game.getPiece(pos("e7")), nullptr);
        ASSERT_TRUE(blackRook->getField() == nullptr);

        ASSERT_EQ(game.getPiece(pos("f8"))->getType(), PieceType::QUEEN);
        ASSERT_EQ(game.getPiece(pos("f8"))->getField(), game.getBoard()->getField(pos("f8")));
        ASSERT_EQ(game.getBlackPlayer()->getPieces().size(), 1);
        ASSERT_TRUE(game.isCheck(Color::BLACK));
        ASSERT_FALSE(game.isMate());

    }

    TEST(Game, insufficientMaterialOnlyKings) {
        auto game = fenGame("k7/8/8/8/8/8/8/K7 w - - 0 1");
        ASSERT_EQ(game.isOver(), GameOver::INSUFFICIENT_MATERIAL);
    }

    TEST(Game, insufficientMaterialKingAndKnightvsKingAndBishop) {
        auto game = fenGame("k6b/8/8/8/8/8/8/K1N5 b - - 0 1");
        ASSERT_EQ(game.isOver(), GameOver::INSUFFICIENT_MATERIAL);
    }

    TEST(Game, insufficientMaterialKingAndKnightvsKing) {
        auto game = fenGame("k7/8/8/8/8/8/8/K1N5 w - - 0 1");
        ASSERT_EQ(game.isOver(), GameOver::INSUFFICIENT_MATERIAL);
    }

    TEST(Game, insufficientMaterialKingAndBishopvsKing) {
        auto game = fenGame("k7/8/8/8/8/8/8/K1B5 b - - 0 1");
        ASSERT_EQ(game.isOver(), GameOver::INSUFFICIENT_MATERIAL);
    }

    TEST(Game, sufficientMaterialKnightBishop) {
        auto game = fenGame("k7/8/8/8/8/7B/8/K1N5 w - - 0 1");
        ASSERT_EQ(game.isOver(), GameOver::NOT_OVER);
    }

    TEST(Game, sufficientMaterialTwoKnights) {
        auto game = fenGame("k7/8/8/8/8/8/8/K1NN4 w - - 0 1");
        ASSERT_EQ(game.isOver(), GameOver::NOT_OVER);
    }

    TEST(Game, sufficientMaterialRook) {
        auto game = fenGame("k7/8/8/8/8/8/K1R5/8 w - - 0 1");
        ASSERT_EQ(game.isOver(), GameOver::NOT_OVER);
    }
}