// Practical 11 - CSV Student Records Using File I/O
// Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059
//
// Writes student records to students.csv and reads them back.
// Also demonstrates the four file-position functions:
//   tellp()/seekp()  -> output (put) position
//   tellg()/seekg()  -> input  (get) position
//
// CSV format (one record per line):  id,name,marks

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Student {
    int         id;
    std::string name;
    int         marks;
};

// --- Write records, demonstrating tellp()/seekp() ---
void writeRecords(const std::string& file, const std::vector<Student>& list) {
    std::ofstream out(file, std::ios::trunc);
    if (!out) {
        std::cerr << "  Could not open " << file << " for writing.\n";
        return;
    }

    out << "id,name,marks\n";
    std::cout << "  After header, put position tellp() = " << out.tellp() << '\n';

    for (const auto& s : list) {
        out << s.id << ',' << s.name << ',' << s.marks << '\n';
    }
    std::cout << "  After all records, tellp() = " << out.tellp() << '\n';

    // seekp demo: jump back to the very start and overwrite the first 2 chars
    // of the header "id" with "ID" (same length, so the format stays valid).
    out.seekp(0, std::ios::beg);
    out << "ID";
    std::cout << "  Used seekp() to rewrite the header start.\n";
}

// --- Read records back, demonstrating tellg()/seekg() ---
void readRecords(const std::string& file) {
    std::ifstream in(file);
    if (!in) {
        std::cerr << "  Could not open " << file << " for reading.\n";
        return;
    }

    std::cout << "  Initial get position tellg() = " << in.tellg() << '\n';

    std::string line;
    std::getline(in, line);   // skip header
    std::cout << "  After reading header, tellg() = " << in.tellg() << '\n';

    // Remember where the data starts, so we can rewind to it later.
    std::streampos dataStart = in.tellg();

    std::cout << "  --- First pass ---\n";
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        std::string idStr, name, marksStr;
        if (!std::getline(ss, idStr, ',') ||
            !std::getline(ss, name,  ',') ||
            !std::getline(ss, marksStr)) {
            std::cout << "    (skipping malformed line: " << line << ")\n";
            continue;
        }
        std::cout << "    ID=" << idStr << " Name=" << name
                  << " Marks=" << marksStr << '\n';
    }

    // seekg demo: rewind to where the data began and read the first record again.
    in.clear();                  // clear the EOF flag set by the loop
    in.seekg(dataStart);
    std::cout << "  --- Used seekg() to re-read the first record ---\n";
    if (std::getline(in, line)) {
        std::cout << "    First record again: " << line << '\n';
    }
}

int main() {
    const std::string file = "students.csv";

    std::vector<Student> students = {
        {1, "Himesh",  88},
        {2, "Riya",    91},
        {3, "Arjun",   76},
    };

    std::cout << "=== Writing records (tellp/seekp) ===\n";
    writeRecords(file, students);

    std::cout << "\n=== Reading records (tellg/seekg) ===\n";
    readRecords(file);

    std::cout << "\nNote: get position is the READ cursor; put position is the\n"
                 "WRITE cursor. They are tracked independently by the stream.\n";
    return 0;
}
