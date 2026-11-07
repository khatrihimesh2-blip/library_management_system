// Practical 01 - GitHub Setup and C++ Fundamentals
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Demonstrates data types, a const value, variables, operators and I/O.
// Computes a simple shopping bill with tax.

#include <iostream>
#include <string>

int main() {
    const double TAX_RATE = 0.18;   // const value: 18% GST

    std::string item;
    int    quantity = 0;
    double price    = 0.0;

    std::cout << "=== Simple Billing Calculator ===\n";
    std::cout << "Enter item name     : ";
    std::getline(std::cin, item);
    std::cout << "Enter unit price     : ";
    std::cin  >> price;
    std::cout << "Enter quantity       : ";
    std::cin  >> quantity;

    // Arithmetic operators
    double subtotal = price * quantity;
    double tax      = subtotal * TAX_RATE;
    double total    = subtotal + tax;

    // Relational + logical operators in a decision
    bool freeDelivery = (total > 500.0) && (quantity >= 1);

    std::cout << "\n--- Bill ---\n";
    std::cout << "Item        : " << item     << '\n';
    std::cout << "Unit price  : " << price    << '\n';
    std::cout << "Quantity    : " << quantity << '\n';
    std::cout << "Subtotal    : " << subtotal << '\n';
    std::cout << "Tax (18%)   : " << tax      << '\n';
    std::cout << "Total       : " << total    << '\n';
    std::cout << "Free delivery? " << (freeDelivery ? "Yes" : "No") << '\n';

    return 0;
}
