// Practical 10 - Custom Exceptions: Banking Transaction
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Custom exception hierarchy:
//   std::exception
//     └── BankException
//           ├── InvalidAmount      (amount <= 0)
//           └── InsufficientFunds  (amount > balance)
//
// A failed withdrawal throws BEFORE changing the balance, so the balance
// never ends up in a wrong state.

#include <iostream>
#include <stdexcept>
#include <string>

class BankException : public std::runtime_error {
public:
    explicit BankException(const std::string& m) : std::runtime_error(m) {}
};
class InvalidAmount : public BankException {
public:
    explicit InvalidAmount(const std::string& m) : BankException(m) {}
};
class InsufficientFunds : public BankException {
public:
    explicit InsufficientFunds(const std::string& m) : BankException(m) {}
};

class BankAccount {
    double balance_;
public:
    explicit BankAccount(double opening) : balance_(opening) {}

    double balance() const { return balance_; }

    void withdraw(double amount) {
        if (amount <= 0)
            throw InvalidAmount("Amount must be positive (got " +
                                std::to_string(amount) + ").");
        if (amount > balance_)
            throw InsufficientFunds("Cannot withdraw " + std::to_string(amount) +
                                    "; balance is only " +
                                    std::to_string(balance_) + ".");
        balance_ -= amount;   // only reached if both checks pass
    }
};

void tryWithdraw(BankAccount& acc, double amount) {
    std::cout << "  Withdraw " << amount << ": ";
    try {
        acc.withdraw(amount);
        std::cout << "OK. New balance = " << acc.balance() << '\n';
    }
    catch (const InvalidAmount& e) {
        std::cout << "[InvalidAmount] " << e.what() << '\n';
    }
    catch (const InsufficientFunds& e) {
        std::cout << "[InsufficientFunds] " << e.what() << '\n';
    }
}

int main() {
    BankAccount acc(1000.0);
    std::cout << "Opening balance: " << acc.balance() << "\n\n";

    tryWithdraw(acc, 300);    // success
    tryWithdraw(acc, -50);    // InvalidAmount
    tryWithdraw(acc, 5000);   // InsufficientFunds
    tryWithdraw(acc, 700);    // success

    std::cout << "\nFinal balance: " << acc.balance() << '\n';
    std::cout << "(Failed transactions did not change the balance.)\n";
    return 0;
}
