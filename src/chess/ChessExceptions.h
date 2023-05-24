#ifndef CHESS_CHESSEXCEPTIONS_H
#define CHESS_CHESSEXCEPTIONS_H

#include <exception>

class ChessException : public std::exception {
private:
    char *message;
public:
    explicit ChessException(char *msg) : message(msg) {}

    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return message;
    }
};

class IllegalMoveException : public ChessException {
    using ChessException::ChessException;
};

class PieceNotOnBoardException : public ChessException {
    using ChessException::ChessException;
};

class FenException : public ChessException {
    using ChessException::ChessException;
};

#endif //CHESS_CHESSEXCEPTIONS_H
