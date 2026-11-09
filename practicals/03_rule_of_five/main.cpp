// Practical 03 - Constructors and Rule of Five
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// IntArray manages a dynamically allocated int array. It demonstrates:
//   default ctor, parameterized ctor, copy ctor, copy assignment,
//   move ctor, move assignment, destructor (the Rule of Five + 2).
//
// Check for leaks with:  valgrind --leak-check=full ./a.out

#include <iostream>
#include <algorithm>   // std::copy
#include <utility>     // std::move

class IntArray {
private:
    std::size_t size_;
    int*        data_;

public:
    // 1. Default constructor
    IntArray() : size_(0), data_(nullptr) {
        std::cout << "[default ctor]\n";
    }

    // 2. Parameterized constructor
    explicit IntArray(std::size_t n, int value = 0)
        : size_(n), data_(n ? new int[n] : nullptr) {
        std::fill(data_, data_ + size_, value);
        std::cout << "[param ctor] size=" << size_ << '\n';
    }

    // 3. Copy constructor  -> deep copy
    IntArray(const IntArray& other)
        : size_(other.size_), data_(other.size_ ? new int[other.size_] : nullptr) {
        std::copy(other.data_, other.data_ + size_, data_);
        std::cout << "[copy ctor] deep-copied " << size_ << " ints\n";
    }

    // 4. Copy assignment  -> deep copy with self-assignment guard
    IntArray& operator=(const IntArray& other) {
        std::cout << "[copy assign]\n";
        if (this != &other) {
            int* newData = other.size_ ? new int[other.size_] : nullptr;
            std::copy(other.data_, other.data_ + other.size_, newData);
            delete[] data_;
            data_ = newData;
            size_ = other.size_;
        }
        return *this;
    }

    // 5. Move constructor  -> steal the pointer, leave source empty
    IntArray(IntArray&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.size_ = 0;
        other.data_ = nullptr;
        std::cout << "[move ctor] ownership transferred\n";
    }

    // 6. Move assignment
    IntArray& operator=(IntArray&& other) noexcept {
        std::cout << "[move assign]\n";
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // 7. Destructor  -> release the owned resource
    ~IntArray() {
        std::cout << "[dtor] freeing size=" << size_ << '\n';
        delete[] data_;
    }

    void set(std::size_t i, int v) { if (i < size_) data_[i] = v; }
    void print() const {
        std::cout << "  [ ";
        for (std::size_t i = 0; i < size_; ++i) std::cout << data_[i] << ' ';
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "-- parameterized --\n";
    IntArray a(3, 7);
    a.set(1, 42);
    a.print();

    std::cout << "\n-- copy constructor --\n";
    IntArray b = a;      // copy ctor
    b.set(0, 99);
    std::cout << "a: "; a.print();   // unchanged -> proves deep copy
    std::cout << "b: "; b.print();

    std::cout << "\n-- move constructor --\n";
    IntArray c = std::move(a);       // move ctor
    c.print();

    std::cout << "\n-- copy assignment --\n";
    IntArray d;          // default ctor
    d = b;               // copy assign

    std::cout << "\n-- move assignment --\n";
    IntArray e;
    e = std::move(c);    // move assign
    e.print();

    std::cout << "\n-- destructors run as objects go out of scope --\n";
    return 0;
}
