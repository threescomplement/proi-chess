#include "../common.h"
#include "../../../src/chess/pieces/Pawn.h"
#include "../../../src/chess/Board.h"
#include "gtest/gtest.h"
#include <algorithm>

using namespace ChessUnitTestCommon;

namespace PawnUnitTest {

    TEST(Pawn, getMoves_basePositionTwoMoves) {
        auto testBoard = Board::fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
        auto testedPawn = testBoard->getField(pos("e2"))->getPiece();
        auto movesForPawn = testedPawn->getMoves();
        ASSERT_EQ(movesForPawn.size(), 2);
        Move expectedMove1 = {pos("e2"), pos("e3"), testedPawn};
        Move expectedMove2 = {pos("e2"), pos("e4"), testedPawn};
        ASSERT_TRUE(in(movesForPawn, expectedMove1));
        ASSERT_TRUE(in(movesForPawn, expectedMove2));
    }


    TEST(Pawn, getMoves_twoAttacksPossible) {
        auto board = Board::fromFEN("rnbqkbnr/ppp1p1pp/8/3p1p2/4P3/8/PPPP1PPP/RNBQKBNR");
        auto pawn = board->getField(pos("e4"))->getPiece();
        auto pawnMoves = pawn->getMoves();

        auto expected = {
                Move(pos("e4"), pos("d5"), pawn, board->getField(pos("d5"))->getPiece()),
                Move(pos("e4"), pos("e5"), pawn),
                Move(pos("e4"), pos("f5"), pawn, board->getField(pos("f5"))->getPiece())
        };
        ASSERT_EQ(3, pawnMoves.size());
        ASSERT_TRUE(isPermutation(pawnMoves, expected));
    }


    TEST(Pawn, getMoves_singleMovePossible) {
        auto board = Board::fromFEN("rnbqkbnr/1ppppppp/8/p7/4P3/8/PPPP1PPP/RNBQKBNR");
        auto pawn = board->getField(pos("e4"))->getPiece();
        auto moves = pawn->getMoves();

        auto expected = {Move(pos("e4"), pos("e5"), pawn)};
        ASSERT_TRUE(isPermutation(moves, expected));
    }

    TEST(Pawn, getMoves_oneAttackPossible) {
        auto board = Board::fromFEN("rnbqkbnr/ppppp1pp/8/5p2/4P3/8/PPPP1PPP/RNBQKBNR");
        auto pawn = board->getField(pos("e4"))->getPiece();
        auto moves = pawn->getMoves();

        auto expected = {
                Move(pos("e4"), pos("e5"), pawn),
                Move(pos("e4"), pos("f5"), pawn, board->getField(pos("f5"))->getPiece()),
        };
        ASSERT_TRUE(isPermutation(moves, expected));
    }

    TEST(Pawn, getmoves_fieldBehindAttackedProtected) {
        auto board = Board::fromFEN("rnbqkbnr/pp2pppp/2p5/3p4/3PP3/8/PPP2PPP/RNBQKBNR");
        auto pawn = board->getField(pos("e4"))->getPiece();
        auto moves = pawn->getMoves();

        auto expected = {
                Move(pos("e4"), pos("e5"), pawn),
                Move(pos("e4"), pos("d5"), pawn, board->getField(pos("d5"))->getPiece())
        };
        ASSERT_TRUE(isPermutation(moves, expected));
    }

    TEST(Pawn, enPassantExpected) {
        auto board = Board::fromFEN("rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR");
        auto whitePawn = board->getField(pos("e5"))->getPiece();
        auto blackPawn = dynamic_cast<Pawn *> (board->getField(pos("d5"))->getPiece());
        blackPawn->setMadeDoubleMove(true);
        auto moves = whitePawn->getMoves();


        auto expected = {
                Move(pos("e5"), pos("e6"), whitePawn, nullptr),
                Move(pos("e5"), pos("d6"), whitePawn, blackPawn)
        };
        ASSERT_TRUE(isPermutation(moves, expected));
    }

    TEST(Pawn, enPassantPosNoEP) {
        auto board = Board::fromFEN("rnbqkbnr/ppppp1pp/8/8/4PpP1/8/PPPP1P1P/RNBQKBNR");
        auto blackPawn = board->getField(pos("f4"))->getPiece();
        auto moves = blackPawn->getMoves();

        auto expected = {
                Move(pos("f4"), pos("f3"), blackPawn, nullptr),
        };
        ASSERT_TRUE(isPermutation(moves, expected));
    }


};