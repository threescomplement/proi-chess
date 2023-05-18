
#include "../../src/chess/Board.h"
#include "../../src/chess/pieces/Pawn.h"
#include "../../src/chess/pieces/Rook.h"
#include "../../src/chess/pieces/Knight.h"
#include "../../src/chess/pieces/Bishop.h"
#include "../../src/chess/pieces/Queen.h"
#include "../../src/chess/pieces/King.h"
#include "../../src/chess/Color.h"
#include "../../src/chess/Player.h"


#include <iostream>
#include "gtest/gtest.h"


namespace BoardUnitTest {
    TEST(Board, constructorInitializesEmptyBoard) {
        auto board = Board();
        ASSERT_EQ("8/8/8/8/8/8/8/8", board.toFEN());
    }

    TEST(Board, startingBoard) {
        auto board = Board::startingBoard();
        ASSERT_EQ("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", board->toFEN());
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

