# UML Class Diagram — Library Management System

Author: Himesh Khatri · Khatrihimesh2@gmail.com · +91 7248952059

```
            +-----------------------------------------------+
            |                    Book                       |
            +-----------------------------------------------+
            | - id_       : int                             |
            | - title_    : string                          |
            | - author_   : string                          |
            | - available_: bool                            |
            +-----------------------------------------------+
            | + Book()                                      |
            | + Book(id, title, author, available)          |
            | + getId() : int                               |
            | + getTitle() : string                         |
            | + getAuthor() : string                        |
            | + isAvailable() : bool                        |
            | + setAvailable(bool)                          |
            | + toCsv() : string                            |
            | + fromCsv(string) : Book   (static)           |
            | + display()                                   |
            +-----------------------------------------------+
                               ^
                               |  "stores many"  (composition)
                               |  std::map<int, Book>
            +-----------------------------------------------+
            |                  Library                      |
            +-----------------------------------------------+
            | - books_    : map<int, Book>                  |
            | - filename_ : string                          |
            +-----------------------------------------------+
            | + addBook(id, title, author)                  |
            | + issueBook(id)                               |
            | + returnBook(id)                              |
            | + getBook(id) : const Book&                   |
            | + searchByTitle(text) : vector<Book>          |
            | + listAll()                                   |
            | + count() : size_t                            |
            | + loadFromFile()                              |
            | + saveToFile()                                |
            +-----------------------------------------------+
                               |
                               |  "throws / catches"
                               v
    +---------------------------------------------------------------+
    |                 LibraryException  (: runtime_error)           |
    +---------------------------------------------------------------+
        ^        ^         ^             ^            ^          ^
        |        |         |             |            |          |
  BookNotFound  Duplicate  BookUnavail   BookNot    InvalidInput  Malformed
                BookId     able          Issued                   Record
```

## Relationships

- **Library  ◆── Book**  (composition): a `Library` owns its `Book` objects,
  held in an STL `std::map<int, Book>` keyed by book ID.
- **LibraryException ◁── (6 subclasses)**: all custom errors inherit from
  `LibraryException`, which itself inherits from `std::runtime_error`. This lets
  `main()` catch any one of them specifically, or all of them as a base class.

## Design notes

| Course concept      | Where it appears                                             |
|---------------------|--------------------------------------------------------------|
| Encapsulation       | `Book` data members are private, exposed via getters/setters |
| STL containers      | `std::map`, `std::vector`, `std::string`                     |
| Inheritance/polymorphism | Exception hierarchy derived from `std::runtime_error`   |
| Exception handling  | Custom exceptions thrown in `Library`, caught in `main`      |
| File I/O            | `loadFromFile()` / `saveToFile()` using `fstream` + CSV      |
