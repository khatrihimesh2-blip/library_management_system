// Book.cpp
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Implementation of the Book class.

#include "Book.h"
#include "LibraryExceptions.h"

#include <iostream>
#include <sstream>
#include <iomanip>

// --- Constructors ---------------------------------------------------------

Book::Book()
    : id_(0), title_(""), author_(""), available_(true) {}

Book::Book(int id, const std::string& title,
           const std::string& author, bool available)
    : id_(id), title_(title), author_(author), available_(available) {}

// --- CSV helpers ----------------------------------------------------------

// A book is stored as:  id,title,author,available
// Commas inside title/author are escaped to ';' to keep the CSV simple.
static std::string sanitize(const std::string& field) {
    std::string out = field;
    for (char& c : out) {
        if (c == ',') c = ';';
    }
    return out;
}

std::string Book::toCsv() const {
    std::ostringstream os;
    os << id_ << ','
       << sanitize(title_) << ','
       << sanitize(author_) << ','
       << (available_ ? 1 : 0);
    return os.str();
}

Book Book::fromCsv(const std::string& line) {
    std::istringstream is(line);
    std::string idStr, title, author, availStr;

    if (!std::getline(is, idStr, ',')  ||
        !std::getline(is, title, ',')  ||
        !std::getline(is, author, ',') ||
        !std::getline(is, availStr)) {
        throw MalformedRecord("Malformed CSV line: \"" + line + "\"");
    }

    int id = 0;
    bool available = true;
    try {
        id        = std::stoi(idStr);
        available = (std::stoi(availStr) != 0);
    } catch (const std::exception&) {
        throw MalformedRecord("Bad numeric field in line: \"" + line + "\"");
    }

    return Book(id, title, author, available);
}

// --- Display --------------------------------------------------------------

void Book::display() const {
    std::cout << std::left
              << "  ID: "    << std::setw(5)  << id_
              << " | "       << std::setw(30) << title_
              << " | "       << std::setw(22) << author_
              << " | "       << (available_ ? "Available" : "Issued")
              << '\n';
}
