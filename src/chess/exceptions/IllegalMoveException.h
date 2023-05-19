#ifndef CHESS_ILLEGALMOVEEXCEPTION_H
#define CHESS_ILLEGALMOVEEXCEPTION_H

#include "../pieces/Piece.h"
#include "../constants.h"
#include "../Move.h"
#include "../Field.h"
#include <utility>
#include <memory>

class IllegalMoveException : public std::exception {
private:
    std::string message;
public:
    explicit IllegalMoveException(std::string msg) : message(std::move(msg)) {}

    std::string what() {
        return message;
    }
};

#endif //CHESS_ILLEGALMOVEEXCEPTION_H
