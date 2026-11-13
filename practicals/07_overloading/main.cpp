// Practical 07 - Compile-Time Polymorphism: Overloading
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Function overloading: same name, different parameter lists.
// Operator overloading: ComplexNumber supports +, -, * and <<.
// The compiler picks the right function at COMPILE time based on types.

#include <iostream>

// --- Function overloading ---
int    add(int a, int b)         { return a + b; }
double add(double a, double b)   { return a + b; }
int    add(int a, int b, int c)  { return a + b + c; }

// --- Operator overloading on a ComplexNumber class ---
class ComplexNumber {
    double re_, im_;
public:
    ComplexNumber(double re = 0, double im = 0) : re_(re), im_(im) {}

    ComplexNumber operator+(const ComplexNumber& o) const {
        return ComplexNumber(re_ + o.re_, im_ + o.im_);
    }
    ComplexNumber operator-(const ComplexNumber& o) const {
        return ComplexNumber(re_ - o.re_, im_ - o.im_);
    }
    ComplexNumber operator*(const ComplexNumber& o) const {
        return ComplexNumber(re_ * o.re_ - im_ * o.im_,
                             re_ * o.im_ + im_ * o.re_);
    }
    // Friend lets us write  cout << c  naturally.
    friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& c) {
        os << c.re_;
        if (c.im_ >= 0) os << " + " << c.im_ << 'i';
        else            os << " - " << -c.im_ << 'i';
        return os;
    }
};

int main() {
    std::cout << "=== Function overloading ===\n";
    std::cout << "  add(2, 3)        = " << add(2, 3) << '\n';
    std::cout << "  add(2.5, 3.1)    = " << add(2.5, 3.1) << '\n';
    std::cout << "  add(1, 2, 3)     = " << add(1, 2, 3) << '\n';

    std::cout << "\n=== Operator overloading (ComplexNumber) ===\n";
    ComplexNumber a(3, 2), b(1, 7);
    std::cout << "  a       = " << a << '\n';
    std::cout << "  b       = " << b << '\n';
    std::cout << "  a + b   = " << (a + b) << '\n';
    std::cout << "  a - b   = " << (a - b) << '\n';
    std::cout << "  a * b   = " << (a * b) << '\n';

    return 0;
}
