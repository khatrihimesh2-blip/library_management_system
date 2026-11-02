// Book.h
// Library Management System - Mini Project (Practical 12, Option A)
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Declares the Book class: encapsulates a single book record.

#ifndef BOOK_H
#define BOOK_H

#include <string>

// Book represents a single library book.
// Data members are private (encapsulation); access is via public getters/setters.
class Book {
private:
    int         id_;          // unique book ID
    std::string title_;       // book title
    std::string author_;      // book author
    bool        available_;   // true = on shelf, false = issued out

public:
    // Constructors
    Book();                                                       // default
    Book(int id, const std::string& title,
         const std::string& author, bool available = true);       // parameterized

    // Getters (const - do not modify the object)
    int                getId()        const { return id_; }
    const std::string& getTitle()     const { return title_; }
    const std::string& getAuthor()    const { return author_; }
    bool               isAvailable()  const { return available_; }

    // Setters / state changes
    void setTitle(const std::string& title)   { title_ = title; }
    void setAuthor(const std::string& author) { author_ = author; }
    void setAvailable(bool available)         { available_ = available; }

    // CSV serialization helpers
    std::string toCsv() const;                 // convert this book to a CSV line
    static Book fromCsv(const std::string& line); // build a Book from a CSV line

    // Display a formatted one-line summary of the book
    void display() const;
};

#endif // BOOK_H
