// main.cpp
// Library Management System - Mini Project (Practical 12, Option A)
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Console-based menu driver. Combines:
//   * OOP            -> Book / Library classes, encapsulation
//   * STL            -> std::map, std::vector, std::string
//   * Exceptions     -> custom LibraryException hierarchy
//   * File I/O       -> CSV load at startup, save on changes/exit

#include "Library.h"
#include "LibraryExceptions.h"

#include <iostream>
#include <string>

namespace {

// Read a full line of text with a prompt.
std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

// Read an integer safely; re-prompts until a valid number is entered.
int readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            // EOF / stream closed -> treat as a request to quit.
            return 0;
        }
        try {
            std::size_t pos = 0;
            int value = std::stoi(line, &pos);
            // Ensure the whole token was a number.
            while (pos < line.size() && std::isspace(static_cast<unsigned char>(line[pos]))) ++pos;
            if (pos == line.size()) return value;
        } catch (const std::exception&) {
            // fall through to the error message
        }
        std::cout << "  Please enter a valid whole number.\n";
    }
}

// Map a book ID to its field, based on the ID range it falls in.
std::string fieldOf(int id) {
    if (id >= 101 && id <= 199) return "Self-Help";
    if (id >= 201 && id <= 299) return "Space";
    if (id >= 301 && id <= 399) return "Biology";
    if (id >= 401 && id <= 499) return "Physics";
    if (id >= 501 && id <= 599) return "Chemistry";
    if (id >= 601 && id <= 699) return "Mathematics";
    if (id >= 701 && id <= 799) return "Other";
    return "Uncategorized";
}

// List every book, grouped under a heading for each field.
void listGrouped(const Library& lib) {
    auto books = lib.search("");   // empty query -> all books, sorted by ID
    if (books.empty()) {
        std::cout << "  (The library is empty.)\n";
        return;
    }
    std::string currentField;
    for (const auto& b : books) {
        std::string field = fieldOf(b.getId());
        if (field != currentField) {           // new section header
            currentField = field;
            std::cout << "\n  ==== " << field << " ====\n";
        }
        b.display();
    }
    std::cout << "\n  Total: " << books.size() << " book(s).\n";
}

void printMenu() {
    std::cout << "\n==============================================\n"
              << "        LIBRARY MANAGEMENT SYSTEM\n"
              << "==============================================\n"
              << "  1. Add a book\n"
              << "  2. List all books\n"
              << "  3. Find a book (by ID, title or author)\n"
              << "  4. Issue a book\n"
              << "  5. Return a book\n"
              << "  6. Save to file\n"
              << "  0. Save and exit\n"
              << "----------------------------------------------\n";
}

void doAddBook(Library& lib) {
    int id = readInt("  Enter book ID: ");
    std::string title  = readLine("  Enter title : ");
    std::string author = readLine("  Enter author: ");
    lib.addBook(id, title, author);
    std::cout << "  Book added successfully.\n";
}

void doSearch(const Library& lib) {
    std::cout << "  Type anything you remember - an ID, part of the title,\n"
                 "  or part of the author's name. Leave blank to see all.\n";
    std::string text = readLine("  Search: ");
    auto results = lib.search(text);
    if (results.empty()) {
        std::cout << "  No books matched \"" << text << "\".\n";
        return;
    }
    std::cout << "  Found " << results.size() << " book(s):\n";
    for (const auto& b : results) {
        b.display();
    }
}

void doIssue(Library& lib) {
    int id = readInt("  Enter ID of book to issue: ");
    lib.issueBook(id);
    std::cout << "  Book issued. Enjoy your reading!\n";
}

void doReturn(Library& lib) {
    int id = readInt("  Enter ID of book to return: ");
    lib.returnBook(id);
    std::cout << "  Book returned. Thank you!\n";
}

} // namespace

int main() {
    const std::string dataFile = "catalog.csv";
    Library library(dataFile);

    // Load existing catalogue (silent if the file does not exist yet).
    library.loadFromFile();
    std::cout << "Loaded " << library.count()
              << " book(s) from " << dataFile << ".\n";

    bool running = true;
    while (running) {
        printMenu();
        int choice = readInt("  Choose an option: ");

        // Each action is wrapped so one bad input never crashes the program.
        try {
            switch (choice) {
                case 1:
                    doAddBook(library);
                    library.saveToFile();
                    break;
                case 2:
                    std::cout << "  Books in the library ("
                              << library.count() << "), grouped by field:\n";
                    listGrouped(library);
                    break;
                case 3:
                    doSearch(library);
                    break;
                case 4:
                    doIssue(library);
                    library.saveToFile();
                    break;
                case 5:
                    doReturn(library);
                    library.saveToFile();
                    break;
                case 6:
                    library.saveToFile();
                    std::cout << "  Catalogue saved to " << dataFile << ".\n";
                    break;
                case 0:
                    library.saveToFile();
                    std::cout << "  Catalogue saved. Goodbye!\n";
                    running = false;
                    break;
                default:
                    std::cout << "  Invalid option. Please choose from the menu.\n";
                    break;
            }
        }
        catch (const LibraryException& e) {
            // All of our application-specific errors land here.
            std::cout << "  [Error] " << e.what() << '\n';
        }
        catch (const std::exception& e) {
            // Any other unexpected standard exception.
            std::cout << "  [Unexpected error] " << e.what() << '\n';
        }
    }

    return 0;
}
