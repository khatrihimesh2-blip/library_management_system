// LibraryExceptions.h
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Custom exception hierarchy for the Library Management System.
// All exceptions derive from std::runtime_error so they carry a message
// and can be caught either specifically or as a std::exception.

#ifndef LIBRARY_EXCEPTIONS_H
#define LIBRARY_EXCEPTIONS_H

#include <stdexcept>
#include <string>

// Base class for every library-specific error.
class LibraryException : public std::runtime_error {
public:
    explicit LibraryException(const std::string& msg)
        : std::runtime_error(msg) {}
};

// Thrown when a book with the requested ID does not exist.
class BookNotFound : public LibraryException {
public:
    explicit BookNotFound(const std::string& msg)
        : LibraryException(msg) {}
};

// Thrown when adding a book whose ID is already in use.
class DuplicateBookId : public LibraryException {
public:
    explicit DuplicateBookId(const std::string& msg)
        : LibraryException(msg) {}
};

// Thrown when trying to issue a book that is already issued out.
class BookUnavailable : public LibraryException {
public:
    explicit BookUnavailable(const std::string& msg)
        : LibraryException(msg) {}
};

// Thrown when returning a book that was not actually issued.
class BookNotIssued : public LibraryException {
public:
    explicit BookNotIssued(const std::string& msg)
        : LibraryException(msg) {}
};

// Thrown when user input is invalid (e.g. non-positive ID, empty title).
class InvalidInput : public LibraryException {
public:
    explicit InvalidInput(const std::string& msg)
        : LibraryException(msg) {}
};

// Thrown when a stored record cannot be parsed from the CSV file.
class MalformedRecord : public LibraryException {
public:
    explicit MalformedRecord(const std::string& msg)
        : LibraryException(msg) {}
};

#endif // LIBRARY_EXCEPTIONS_H
