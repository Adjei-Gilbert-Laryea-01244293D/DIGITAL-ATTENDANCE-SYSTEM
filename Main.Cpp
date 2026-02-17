#include <iostream>
#include <vector>
#include <string>

class Student {
public:
    std::string indexNumber;
    std::string name;
    Student(std::string idx, std::string n) : indexNumber(idx), name(n) {}
    void display() {
        std::cout << "Index: " << indexNumber << ", Name: " << name << "\n";
    }
};

std::vector<Student> students;

void addStudent() {
    std::string idx, name;
    std::cout << "Enter Index Number: ";
    std::cin >> idx;
    std::cout << "Enter Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    students.emplace_back(idx, name);
}

void viewStudents() {
    for (auto& s : students) s.display();
}

int main() {
    int choice;
    do {
        std::cout << "1. Add Student\n2. View Students\n3. Exit\n";
        std::cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
        }
    } while (choice != 3);
    return 0;
}
