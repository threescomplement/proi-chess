#ifndef CHESS_CLIEXCEPTIONS_H
#define CHESS_CLIEXCEPTIONS_H

#include <string>

class CLIException : public std::exception {
private:
    std::string message;
public:
    explicit CLIException(std::string msg) : message(std::move(msg)) {}

    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return message.c_str();
    }
};

class InvalidPlayerInputException : public CLIException {
    using CLIException::CLIException;
};

#endif //CHESS_CLIEXCEPTIONS_H
