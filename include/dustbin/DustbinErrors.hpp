#ifndef RECYCLING_DUSTBINERRORS_HPP
#define RECYCLING_DUSTBINERRORS_HPP

#include <exception>

class DustbinContentError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Dustbin content error.";
    }
};

class BottleCapException : public std::exception {
public:
    const char* what() const noexcept override {
        return "I want pink bottlecaps!";
    }
};

class DustbinFullError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Dustbin is full.";
    }
};

#endif //RECYCLING_DUSTBINERRORS_HPP
