#include "gtest/gtest.h"
#include "Board.h"
#include "FENParser.h"
#include "Color.h"
#include "Game.h"
#include "Player.h"
#include "pieces/Rook.h"
#include "pieces/Knight.h"
#include "pieces/Bishop.h"
#include "pieces/Queen.h"
#include "pieces/King.h"
#include "pieces/Pawn.h"
#include "common.h"

using namespace ChessUnitTestCommon;

namespace FENParserUnitTest {

    TEST(FENParser, boardEmpty) {
        auto testBoard = Board::emptyBoard();
        std::string expected = "8/8/8/8/8/8/8/8";
        ASSERT_EQ(expected, FENParser::boardToString(*testBoard));
        Board *copyFromFen = FENParser::parseBoard(FENParser::boardToString(*testBoard));
        ASSERT_EQ(expected, FENParser::boardToString(*copyFromFen));
    }

    TEST(FENParser, boardStartingState) {
        auto testBoard = Board::emptyBoard();
        std::vector<Piece *> allPieces = {};

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
        ASSERT_EQ(expected, FENParser::boardToString(*testBoard));
        Board *copyFromFen = FENParser::parseBoard(FENParser::boardToString(*testBoard));
        ASSERT_EQ(expected, FENParser::boardToString(*copyFromFen));
    }

    TEST(FENParser, gameGoofyItalian) {
        auto testBoard = Board::emptyBoard();
        std::vector<Piece *> allPieces = {};

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
        ASSERT_EQ(expected, FENParser::boardToString(*testBoard));

        Board *copyFromFen = FENParser::parseBoard(FENParser::boardToString(*testBoard));
        ASSERT_EQ(expected, FENParser::boardToString(*copyFromFen));
    }

    TEST(FENParser, gameStartingState) {
        auto game = FENParser::parseGame("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        auto newGame = Game();
        ASSERT_EQ(FENParser::gameToString(newGame), FENParser::gameToString(game));
        ASSERT_EQ(16, game.getWhitePlayer()->getPieces().size());
        ASSERT_EQ(16, game.getBlackPlayer()->getPieces().size());
    }

    TEST(FENParser, gameAfterMoves) {
        auto fenGame = FENParser::parseGame("rnbqkbnr/pppp1ppp/8/4p3/4P3/7N/PPPP1PPP/RNBQKB1R b KQkq - 1 2");

        auto game = Game();
        game.makeMove(Move(pos("e2"), pos("e4"), game.getPiece(pos("e2"))));
        game.makeMove(Move(pos("e7"), pos("e5"), game.getPiece(pos("e7"))));
        game.makeMove(Move(pos("g1"), pos("h3"), game.getPiece(pos("g1"))));

        ASSERT_EQ(FENParser::gameToString(game), FENParser::gameToString(fenGame));
        ASSERT_EQ(16, game.getWhitePlayer()->getPieces().size());
        ASSERT_EQ(16, game.getBlackPlayer()->getPieces().size());
    }

    TEST(FENParser, gameCastling) {
        auto game = FENParser::parseGame("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w - - 0 1");
        auto whiteKing = game.getPiece(pos("e1"));
        auto blackKing = game.getPiece(pos("e8"));
        auto whiteKingsideCastle = Move(pos("e1"), pos("g1"), whiteKing, nullptr);
        auto blackKingsideCastle = Move(pos("e8"), pos("g8"), blackKing, nullptr);
        auto whiteQueensideCastle = Move(pos("e1"), pos("c1"), whiteKing, nullptr);
        auto blackQueensideCastle = Move(pos("e8"), pos("c8"), blackKing, nullptr);

        auto whiteKingMoves = game.getMovesFrom(pos("e1"));
        auto blackKingMoves = game.getMovesFrom(pos("e8"));

        ASSERT_FALSE(in(blackKingMoves, blackKingsideCastle));
        ASSERT_FALSE(in(blackKingMoves, blackQueensideCastle));
        ASSERT_FALSE(in(whiteKingMoves, whiteKingsideCastle));
        ASSERT_FALSE(in(whiteKingMoves, whiteQueensideCastle));
        ASSERT_EQ(whiteKingMoves.size(), 2);
        ASSERT_EQ(blackKingMoves.size(), 2);
    }
}