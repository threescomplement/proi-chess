#include "../../src/chess/Board.h"
#include "../../src/chess/pieces/Pawn.h"
#include "../../src/chess/pieces/Rook.h"
#include "../../src/chess/pieces/Knight.h"
#include "../../src/chess/pieces/Bishop.h"
#include "../../src/chess/pieces/Queen.h"
#include "../../src/chess/pieces/King.h"
#include "../../src/chess/Color.h"
#include "../../src/chess/Player.h"
#include "../../src/chess/exceptions/PieceNotOnBoardException.h"
#include "common.h"

#include <iostream>
#include "gtest/gtest.h"
#include "exceptions/IllegalMoveException.h"

using namespace ChessUnitTestCommon;

namespace BoardUnitTest {
    TEST(Board, constructorInitializesEmptyBoard) {
        auto board = Board();
        ASSERT_EQ("8/8/8/8/8/8/8/8", board.toFEN());
    }

    TEST(Board, startingBoard) {
        auto board = Board::startingBoard();
        ASSERT_EQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", board->toFEN());
    }

    TEST(Board, makeMoveNoCapture) {
        auto board = Board::startingBoard();
        auto pawn = board->getField(pos("e2"))->getPiece();
        auto move = Move(pos("e2"), pos("e4"), pawn);

        board->makeMove(move);

        ASSERT_EQ("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR", board->toFEN());

        ASSERT_EQ(pos("e4"), pawn->getPosition());
        ASSERT_EQ(board->getField(pos("e4")), pawn->getField());
        ASSERT_EQ(pawn, board->getField(pos("e4"))->getPiece());

        ASSERT_TRUE(board->getField(pos("e2"))->isEmpty());
        ASSERT_FALSE(board->getField(pos("e4"))->isEmpty());
    }

    TEST(Board, makeMoveFromEmptyField) {
        auto board = Board::startingBoard();
        auto pawn = board->getField(pos("e2"))->getPiece();
        auto move = Move(pos("e4"), pos("e5"), pawn);

        ASSERT_THROW(board->makeMove(move), IllegalMoveException);
    }

    TEST(Board, makeMoveCapturePieceOfSameColor) {
        auto board = Board::startingBoard();
        auto knight = board->getField(pos("g1"))->getPiece();
        auto move = Move(pos("g1"), pos("e2"), knight);

        ASSERT_THROW(board->makeMove(move), IllegalMoveException);
    }

    TEST(Board, makeMoveCapture) {
        auto board = Board::fromFEN("rnbqkbnr/pppp1ppp/8/4p3/8/5N2/PPPPPPPP/RNBQKB1R");
        auto knight = board->getField(pos("f3"))->getPiece();
        auto pawn = board->getField(pos("e5"))->getPiece();
        auto move = Move(pos("f3"), pos("e5"), knight, pawn);

        board->makeMove(move);

        ASSERT_EQ("rnbqkbnr/pppp1ppp/8/4N3/8/8/PPPPPPPP/RNBQKB1R", board->toFEN());

        ASSERT_EQ(pos("e5"), knight->getPosition());
        ASSERT_EQ(knight, board->getField(pos("e5"))->getPiece());
        ASSERT_EQ(board->getField(pos("e5")), knight->getField());

        ASSERT_THROW(pawn->getPosition(), PieceNotOnBoardException);
        ASSERT_EQ(nullptr, board->getField(pos("f3"))->getPiece());
        ASSERT_EQ(nullptr, pawn->getField());


        ASSERT_TRUE(board->getField(pos("f3"))->isEmpty());
        ASSERT_FALSE(board->getField(pos("e5"))->isEmpty());
    }

    TEST(Board, FEN_emptyBoard) {
        auto testBoard = Board::emptyBoard();
        std::string expected = "8/8/8/8/8/8/8/8";
        ASSERT_EQ(expected, testBoard->toFEN());
        Board *copyFromFen = Board::fromFEN(testBoard->toFEN());
        ASSERT_EQ(expected, copyFromFen->toFEN());
    }

    TEST(Board, FEN_initialBoardState) {
        auto testBoard = Board::emptyBoard();
        std::vector<Piece *> allPieces = {};
        auto whitePlayer = new Player(std::string("White Player"));
        auto blackPlayer = new Player(std::string("Black Player"));

        {
            allPieces.push_back(new Rook(Color::WHITE, testBoard->getField(Position(1, 1))));
            allPieces.push_back(new Knight(Color::WHITE, testBoard->getField(Position(1, 2))));
            allPieces.push_back(new Bishop(Color::WHITE, testBoard->getField(Position(1, 3))));
            allPieces.push_back(new Queen(Color::WHITE, testBoard->getField(Position(1, 4))));
            allPieces.push_back(new King(Color::WHITE, testBoard->getField(Position(1, 5))));
            allPieces.push_back(new Bishop(Color::WHITE, testBoard->getField(Position(1, 6))));
            allPieces.push_back(new Knight(Color::WHITE, testBoard->getField(Position(1, 7))));
            allPieces.push_back(new Rook(Color::WHITE, testBoard->getField(Position(1, 8))));

            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 1))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 2))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 3))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 4))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 5))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 6))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 7))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 8))));

            allPieces.push_back(new Rook(Color::BLACK, testBoard->getField(Position(8, 1))));
            allPieces.push_back(new Knight(Color::BLACK, testBoard->getField(Position(8, 2))));
            allPieces.push_back(new Bishop(Color::BLACK, testBoard->getField(Position(8, 3))));
            allPieces.push_back(new Queen(Color::BLACK, testBoard->getField(Position(8, 4))));
            allPieces.push_back(new King(Color::BLACK, testBoard->getField(Position(8, 5))));
            allPieces.push_back(new Bishop(Color::BLACK, testBoard->getField(Position(8, 6))));
            allPieces.push_back(new Knight(Color::BLACK, testBoard->getField(Position(8, 7))));
            allPieces.push_back(new Rook(Color::BLACK, testBoard->getField(Position(8, 8))));

            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 1))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 2))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 3))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 4))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 5))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 6))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 7))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 8))));
        }

        for (Piece *piece: allPieces) {
            piece->getField()->setPiece(piece);
        }

        std::string expected = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
        ASSERT_EQ(expected, testBoard->toFEN());
        Board *copyFromFen = Board::fromFEN(testBoard->toFEN());
        ASSERT_EQ(expected, copyFromFen->toFEN());
    }

    TEST(Board, FEN_goofyItalian) {
        auto testBoard = Board::emptyBoard();
        std::vector<Piece *> allPieces = {};
        auto whitePlayer = new Player(std::string("White Player"));
        auto blackPlayer = new Player(std::string("Black Player"));

        {
            allPieces.push_back(new Rook(Color::WHITE, testBoard->getField(Position(1, 1))));
            allPieces.push_back(new Knight(Color::WHITE, testBoard->getField(Position(1, 2))));
            allPieces.push_back(new Bishop(Color::WHITE, testBoard->getField(Position(1, 3))));
            allPieces.push_back(new Queen(Color::WHITE, testBoard->getField(Position(1, 4))));
            allPieces.push_back(new King(Color::WHITE, testBoard->getField(Position(1, 5))));
            allPieces.push_back(new Bishop(Color::WHITE, testBoard->getField(Position(4, 3))));
            allPieces.push_back(new Knight(Color::WHITE, testBoard->getField(Position(3, 6))));
            allPieces.push_back(new Rook(Color::WHITE, testBoard->getField(Position(1, 8))));

            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 1))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 2))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 3))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 4))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(4, 5))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 6))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 7))));
            allPieces.push_back(new Pawn(Color::WHITE, testBoard->getField(Position(2, 8))));

            allPieces.push_back(new Rook(Color::BLACK, testBoard->getField(Position(8, 1))));
            allPieces.push_back(new Knight(Color::BLACK, testBoard->getField(Position(6, 3))));
            allPieces.push_back(new Bishop(Color::BLACK, testBoard->getField(Position(8, 3))));
            allPieces.push_back(new Queen(Color::BLACK, testBoard->getField(Position(8, 4))));
            allPieces.push_back(new King(Color::BLACK, testBoard->getField(Position(8, 5))));
            allPieces.push_back(new Bishop(Color::BLACK, testBoard->getField(Position(8, 6))));
            allPieces.push_back(new Knight(Color::BLACK, testBoard->getField(Position(8, 7))));
            allPieces.push_back(new Rook(Color::BLACK, testBoard->getField(Position(8, 8))));

            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(6, 1))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 2))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 3))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(5, 4))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 5))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 6))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 7))));
            allPieces.push_back(new Pawn(Color::BLACK, testBoard->getField(Position(7, 8))));
        }

        for (Piece *piece: allPieces) {
            piece->getField()->setPiece(piece);
        }

        std::string expected = "r1bqkbnr/1pp1pppp/p1n5/3p4/2B1P3/5N2/PPPP1PPP/RNBQK2R";
        ASSERT_EQ(expected, testBoard->toFEN());

        Board *copyFromFen = Board::fromFEN(testBoard->toFEN());
        ASSERT_EQ(expected, copyFromFen->toFEN());
    }
}

