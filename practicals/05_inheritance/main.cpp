// Practical 05 - Single and Multilevel Inheritance
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Person  ->  Student  ->  GraduateStudent
//   single inheritance:     Person -> Student
//   multilevel inheritance: Person -> Student -> GraduateStudent

#include <iostream>
#include <string>

class Person {
protected:
    std::string name_;
    int         age_;
public:
    Person(const std::string& name, int age) : name_(name), age_(age) {}
    void displayPerson() const {
        std::cout << "  Name: " << name_ << ", Age: " << age_ << '\n';
    }
};

// Single inheritance: Student IS-A Person
class Student : public Person {
protected:
    std::string studentId_;
    std::string course_;
public:
    Student(const std::string& name, int age,
            const std::string& id, const std::string& course)
        : Person(name, age), studentId_(id), course_(course) {}
    void displayStudent() const {
        displayPerson();                         // reused from Person
        std::cout << "  ID: " << studentId_
                  << ", Course: " << course_ << '\n';
    }
};

// Multilevel inheritance: GraduateStudent IS-A Student IS-A Person
class GraduateStudent : public Student {
private:
    std::string researchTopic_;
    std::string supervisor_;
public:
    GraduateStudent(const std::string& name, int age,
                    const std::string& id, const std::string& course,
                    const std::string& topic, const std::string& supervisor)
        : Student(name, age, id, course),
          researchTopic_(topic), supervisor_(supervisor) {}
    void displayGraduate() const {
        displayStudent();                        // reused from Student
        std::cout << "  Research: " << researchTopic_
                  << ", Supervisor: " << supervisor_ << '\n';
    }
};

int main() {
    std::cout << "=== Student (single inheritance) ===\n";
    Student s("Aarav", 20, "S101", "B.Sc Computer Science");
    s.displayStudent();   // has access to Person + Student members

    std::cout << "\n=== GraduateStudent (multilevel inheritance) ===\n";
    GraduateStudent g("Meera", 24, "G205", "M.Tech AI",
                      "Neural Networks", "Dr. Rao");
    g.displayGraduate();  // has access to Person + Student + GraduateStudent

    return 0;
}
