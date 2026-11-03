// Library.h
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Declares the Library class: manages the collection of books in memory
// (using an STL container) and persists them to a CSV file.

#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"

#include <map>
#include <string>
#include <vector>

// Library owns the whole book catalogue.
// Books are stored in a std::map keyed by ID for fast lookup by ID.
class Library {
private:
    std::map<int, Book> books_;   // STL container: id -> Book
    std::string         filename_; // CSV file used for persistence

public:
    explicit Library(const std::string& filename = "books.csv");

    // Core operations -----------------------------------------------------
    void addBook(int id, const std::string& title, const std::string& author);
    void issueBook(int id);     // mark a book as issued (throws if unavailable)
    void returnBook(int id);    // mark a book as returned (throws if not issued)

    // Queries -------------------------------------------------------------
    const Book&              getBook(int id) const;        // throws BookNotFound
    std::vector<Book>        searchByTitle(const std::string& text) const;
    // Flexible search: matches the text against ID, title OR author.
    std::vector<Book>        search(const std::string& text) const;
    void                     listAll() const;              // print every book
    std::size_t              count() const { return books_.size(); }

    // Persistence ---------------------------------------------------------
    void loadFromFile();        // read catalogue from CSV at startup
    void saveToFile() const;    // write catalogue back to CSV
};

#endif // LIBRARY_H
