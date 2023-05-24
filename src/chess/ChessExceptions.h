#ifndef CHESS_CHESSEXCEPTIONS_H
#define CHESS_CHESSEXCEPTIONS_H

#include <exception>
#include <utility>

class ChessException : public std::exception {
private:
    std::string message;
public:
    explicit ChessException(std::string msg) : message(std::move(msg)) {}

    [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return message.c_str();
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
