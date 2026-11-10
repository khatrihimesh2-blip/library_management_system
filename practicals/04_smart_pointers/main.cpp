// Practical 04 - RAII and Smart Pointers
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Shows std::unique_ptr (single owner) and std::shared_ptr (shared ownership).
// RAII: the resource is freed automatically when the owning pointer dies.
//
// Memory check:  valgrind --leak-check=full ./a.out   (expect 0 leaks)

#include <iostream>
#include <memory>
#include <string>

class Resource {
    std::string name_;
public:
    explicit Resource(std::string name) : name_(std::move(name)) {
        std::cout << "  Resource '" << name_ << "' acquired\n";
    }
    ~Resource() {
        std::cout << "  Resource '" << name_ << "' released\n";
    }
    void use() const { std::cout << "  using '" << name_ << "'\n"; }
};

int main() {
    std::cout << "=== unique_ptr: exactly one owner ===\n";
    {
        std::unique_ptr<Resource> u = std::make_unique<Resource>("Printer");
        u->use();
        // Ownership can be MOVED, never copied.
        std::unique_ptr<Resource> u2 = std::move(u);
        std::cout << "  after move, original is "
                  << (u ? "non-null" : "null") << '\n';
        u2->use();
    } // u2 goes out of scope -> Resource freed automatically

    std::cout << "\n=== shared_ptr: shared ownership ===\n";
    {
        std::shared_ptr<Resource> s1 = std::make_shared<Resource>("Database");
        std::cout << "  use_count = " << s1.use_count() << '\n';
        {
            std::shared_ptr<Resource> s2 = s1;   // both own it now
            std::cout << "  use_count = " << s1.use_count() << '\n';
            s2->use();
        } // s2 dies, but the Resource stays alive (s1 still owns it)
        std::cout << "  after inner scope, use_count = " << s1.use_count() << '\n';
    } // last owner dies -> Resource freed

    std::cout << "\n=== unique_ptr managing an array ===\n";
    {
        auto arr = std::make_unique<int[]>(5);
        for (int i = 0; i < 5; ++i) arr[i] = i * i;
        std::cout << "  squares: ";
        for (int i = 0; i < 5; ++i) std::cout << arr[i] << ' ';
        std::cout << '\n';
    } // array freed automatically

    std::cout << "\nNo manual delete was ever called. RAII handled it all.\n";
    return 0;
}
