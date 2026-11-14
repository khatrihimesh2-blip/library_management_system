// Practical 09 - Generic Stack Using Templates
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// A single class template Stack<T> works for int, float and std::string.
// Without templates we would need three near-identical classes.

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

template <typename T>
class Stack {
private:
    std::vector<T> data_;   // STL vector does the storage work
public:
    void push(const T& value) { data_.push_back(value); }

    void pop() {
        if (empty()) throw std::out_of_range("pop() on empty stack");
        data_.pop_back();
    }

    const T& top() const {
        if (empty()) throw std::out_of_range("top() on empty stack");
        return data_.back();
    }

    bool        empty() const { return data_.empty(); }
    std::size_t size()  const { return data_.size();  }
};

template <typename T>
void drain(Stack<T>& s, const std::string& label) {
    std::cout << "  " << label << " (top first): ";
    while (!s.empty()) {
        std::cout << s.top() << ' ';
        s.pop();
    }
    std::cout << '\n';
}

int main() {
    std::cout << "=== Stack<int> ===\n";
    Stack<int> si;
    si.push(1); si.push(2); si.push(3);
    drain(si, "ints");

    std::cout << "\n=== Stack<float> ===\n";
    Stack<float> sf;
    sf.push(1.1f); sf.push(2.2f);
    drain(sf, "floats");

    std::cout << "\n=== Stack<std::string> ===\n";
    Stack<std::string> ss;
    ss.push("alpha"); ss.push("beta"); ss.push("gamma");
    drain(ss, "strings");

    std::cout << "\n=== Error case: pop on empty stack ===\n";
    try {
        Stack<int> empty;
        empty.pop();
    } catch (const std::out_of_range& e) {
        std::cout << "  Caught: " << e.what() << '\n';
    }
    return 0;
}
