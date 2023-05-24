#ifndef CHESS_FENEXCEPTION_H
#define CHESS_FENEXCEPTION_H


#include <string>

class FenException : public std::exception {
private:
    std::string message;
public:
    explicit FenException(std::string msg) : message(std::move(msg)) {}

    std::string what() {
        return message;
    }
};


#endif //CHESS_FENEXCEPTION_H
