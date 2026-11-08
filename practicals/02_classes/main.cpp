// Practical 02 - Classes, Access Specifiers and Member Functions
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// A BankAccount class. Data members are PRIVATE so the balance can never be
// set to an invalid value directly; all access goes through PUBLIC methods
// that validate input. This is encapsulation.

#include <iostream>
#include <string>

class BankAccount {
private:
    // PRIVATE: hidden from outside code. The balance can only change through
    // deposit()/withdraw(), which enforce the rules.
    std::string accountNumber_;
    std::string holder_;
    double      balance_;

public:
    // PUBLIC: the interface the outside world is allowed to use.
    BankAccount(const std::string& number, const std::string& holder,
                double opening = 0.0)
        : accountNumber_(number), holder_(holder),
          balance_(opening < 0 ? 0.0 : opening) {}

    void deposit(double amount) {
        if (amount <= 0) {
            std::cout << "  Deposit must be positive.\n";
            return;
        }
        balance_ += amount;
        std::cout << "  Deposited " << amount << '\n';
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "  Withdrawal must be positive.\n";
            return;
        }
        if (amount > balance_) {
            std::cout << "  Insufficient balance.\n";
            return;
        }
        balance_ -= amount;
        std::cout << "  Withdrew " << amount << '\n';
    }

    void display() const {
        std::cout << "  Account " << accountNumber_ << " (" << holder_
                  << ") balance: " << balance_ << '\n';
    }
};

int main() {
    BankAccount a1("AC1001", "Himesh", 1000.0);
    BankAccount a2("AC1002", "Riya",   500.0);

    std::cout << "Initial state:\n";
    a1.display();
    a2.display();

    std::cout << "\nOperations:\n";
    a1.deposit(250);
    a1.withdraw(2000);   // rejected: insufficient
    a1.withdraw(300);
    a2.deposit(-50);     // rejected: not positive
    a2.deposit(1000);

    std::cout << "\nFinal state:\n";
    a1.display();
    a2.display();
    return 0;
}
