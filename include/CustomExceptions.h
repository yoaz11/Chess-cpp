#pragma once
#include <exception>
#include <string>

/**
 * @class InvalidMoveException
 * @brief Exception for invalid moves.
 */
class InvalidMoveException : public std::exception {
private:
    std::string message;
public:

    /**
     * @brief Constructs an InvalidMoveException with the given message.
     * @param msg The exception message.
     */
    InvalidMoveException(const std::string& msg) : message(msg) {}

    /**
     * @brief Gets the exception message.
     * @return The exception message.
     */
    const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class OutOfBoundsException
 * @brief Exception for out-of-bounds errors.
 */
class OutOfBoundsException : public std::exception {
private:
    std::string message;
public:

    /**
     * @brief Constructs an OutOfBoundsException with the given message.
     * @param msg The exception message.
     */
    OutOfBoundsException(const std::string& msg) : message(msg) {}

    /**
     * @brief Gets the exception message.
     * @return The exception message.
     */
    const char* what() const noexcept override {
        return message.c_str();
    }
};
