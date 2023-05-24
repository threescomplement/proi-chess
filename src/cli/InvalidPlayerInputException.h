#ifndef CHESS_INVALIDPLAYERINPUTEXCEPTION_H
#define CHESS_INVALIDPLAYERINPUTEXCEPTION_H

#include <exception>

class InvalidPlayerInputException : public ChessException {
    using ChessException::ChessException;
};

#endif //CHESS_INVALIDPLAYERINPUTEXCEPTION_H
