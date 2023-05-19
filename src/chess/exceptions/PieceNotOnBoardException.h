#ifndef CHESS_PIECENOTONBOARDEXCEPTION_H
#define CHESS_PIECENOTONBOARDEXCEPTION_H


#include <exception>
#include <string>
#include <utility>

class PieceNotOnBoardException : public std::exception {
    std::string message;

public:
    PieceNotOnBoardException(std::string msg) : message(std::move(msg)) {};

    std::string what() {
        return message;
    }
};


#endif //CHESS_PIECENOTONBOARDEXCEPTION_H
