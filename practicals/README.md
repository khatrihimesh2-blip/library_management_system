# C++ Practicals 01–11

Solutions to Practicals 01–11 of the C++ Programming Practical Manual.
(Practical 12, the Library Management System mini project, is in the parent folder.)

**Author:** Himesh Khatri · Khatrihimesh2@gmail.com · +91 7248952059

## Index

| # | Folder | Topic | Key concept shown |
|---|--------|-------|-------------------|
| 01 | [01_fundamentals](01_fundamentals/main.cpp) | C++ fundamentals | variables, `const`, operators, I/O |
| 02 | [02_classes](02_classes/main.cpp) | Classes & access specifiers | encapsulation, `BankAccount` |
| 03 | [03_rule_of_five](03_rule_of_five/main.cpp) | Constructors & Rule of Five | deep copy vs. move, destructor |
| 04 | [04_smart_pointers](04_smart_pointers/main.cpp) | RAII & smart pointers | `unique_ptr`, `shared_ptr` |
| 05 | [05_inheritance](05_inheritance/main.cpp) | Inheritance | Person → Student → GraduateStudent |
| 06 | [06_polymorphism](06_polymorphism/main.cpp) | Runtime polymorphism | abstract `Shape`, virtual `area()` |
| 07 | [07_overloading](07_overloading/main.cpp) | Compile-time polymorphism | function + operator overloading |
| 08 | [08_factory](08_factory/main.cpp) | Design pattern | Factory pattern (shapes) |
| 09 | [09_templates](09_templates/main.cpp) | Templates | generic `Stack<T>` |
| 10 | [10_exceptions](10_exceptions/main.cpp) | Custom exceptions | banking: InvalidAmount / InsufficientFunds |
| 11 | [11_file_io](11_file_io/main.cpp) | File I/O | CSV + `tellg/seekg/tellp/seekp` |

## Build & run any practical

```bash
cd 03_rule_of_five
g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o app
./app
```

All programs compile cleanly with `-Wall -Wextra` on g++ (C++17).

## Notes for specific practicals

- **03 & 04** — memory-safe by design. To verify with Valgrind:
  `valgrind --leak-check=full ./app` (expect "0 bytes in use", no leaks).
- **06** — `Shape` is abstract; uncommenting `Shape s;` in `main` produces the
  expected compile error, proving abstract classes cannot be instantiated.
- **08** — only the Factory pattern is implemented (the manual says choose one).
- **11** — running the program creates `students.csv` in that folder.
