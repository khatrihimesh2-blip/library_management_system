// Library.cpp
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Implementation of the Library class.

#include "Library.h"
#include "LibraryExceptions.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>

// --- Construction ---------------------------------------------------------

Library::Library(const std::string& filename)
    : filename_(filename) {}

// --- Helpers --------------------------------------------------------------

// Case-insensitive "does haystack contain needle?"
static bool containsIgnoreCase(const std::string& haystack,
                               const std::string& needle) {
    auto toLower = [](std::string s) {
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return s;
    };
    const std::string h = toLower(haystack);
    const std::string n = toLower(needle);
    return h.find(n) != std::string::npos;
}

// --- Core operations ------------------------------------------------------

void Library::addBook(int id, const std::string& title,
                      const std::string& author) {
    if (id <= 0) {
        throw InvalidInput("Book ID must be a positive number.");
    }
    if (title.empty()) {
        throw InvalidInput("Book title cannot be empty.");
    }
    if (books_.count(id) != 0) {
        throw DuplicateBookId("A book with ID " + std::to_string(id) +
                              " already exists.");
    }
    books_.emplace(id, Book(id, title, author, true));
}

void Library::issueBook(int id) {
    auto it = books_.find(id);
    if (it == books_.end()) {
        throw BookNotFound("No book found with ID " + std::to_string(id) + ".");
    }
    if (!it->second.isAvailable()) {
        throw BookUnavailable("Book \"" + it->second.getTitle() +
                              "\" is already issued out.");
    }
    it->second.setAvailable(false);
}

void Library::returnBook(int id) {
    auto it = books_.find(id);
    if (it == books_.end()) {
        throw BookNotFound("No book found with ID " + std::to_string(id) + ".");
    }
    if (it->second.isAvailable()) {
        throw BookNotIssued("Book \"" + it->second.getTitle() +
                            "\" was not issued, so it cannot be returned.");
    }
    it->second.setAvailable(true);
}

// --- Queries --------------------------------------------------------------

const Book& Library::getBook(int id) const {
    auto it = books_.find(id);
    if (it == books_.end()) {
        throw BookNotFound("No book found with ID " + std::to_string(id) + ".");
    }
    return it->second;
}

std::vector<Book> Library::searchByTitle(const std::string& text) const {
    std::vector<Book> results;
    for (const auto& entry : books_) {
        if (containsIgnoreCase(entry.second.getTitle(), text)) {
            results.push_back(entry.second);
        }
    }
    return results;
}

// Flexible search: a match on the ID, the title OR the author all count.
// An empty query returns every book (acts like "show all").
std::vector<Book> Library::search(const std::string& text) const {
    std::vector<Book> results;
    for (const auto& entry : books_) {
        const Book& b = entry.second;
        const std::string idStr = std::to_string(b.getId());
        if (text.empty() ||
            containsIgnoreCase(idStr,          text) ||
            containsIgnoreCase(b.getTitle(),   text) ||
            containsIgnoreCase(b.getAuthor(),  text)) {
            results.push_back(b);
        }
    }
    return results;
}

void Library::listAll() const {
    if (books_.empty()) {
        std::cout << "  (The library is empty.)\n";
        return;
    }
    for (const auto& entry : books_) {
        entry.second.display();
    }
}

// --- Persistence ----------------------------------------------------------

void Library::loadFromFile() {
    std::ifstream in(filename_);
    if (!in) {
        // Not an error on first run: the file simply does not exist yet.
        return;
    }

    std::string line;
    std::size_t lineNo = 0;
    while (std::getline(in, line)) {
        ++lineNo;
        if (line.empty()) continue;
        // Skip an optional header line.
        if (lineNo == 1 && line.rfind("id,", 0) == 0) continue;

        try {
            Book b = Book::fromCsv(line);
            books_[b.getId()] = b;
        } catch (const MalformedRecord& e) {
            std::cerr << "  Warning (skipping line " << lineNo << "): "
                      << e.what() << '\n';
        }
    }
}

void Library::saveToFile() const {
    std::ofstream out(filename_, std::ios::trunc);
    if (!out) {
        throw LibraryException("Could not open \"" + filename_ +
                               "\" for writing.");
    }

    out << "id,title,author,available\n";   // header row
    for (const auto& entry : books_) {
        out << entry.second.toCsv() << '\n';
        if (!out) {
            throw LibraryException("Error while writing to \"" +
                                   filename_ + "\".");
        }
    }
}
