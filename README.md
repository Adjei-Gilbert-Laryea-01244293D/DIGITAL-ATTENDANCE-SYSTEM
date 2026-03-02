#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// ================= STUDENT CLASS =================
class Student {
public:
    string indexNumber;
    string name;

    Student(string idx = "", string nm = "") {
        indexNumber = idx;
        name = nm;
    }
};

// ================= SAVE STUDENT =================
void saveStudent(Student s) {
    ofstream file("students.txt", ios::app);
    if (file.is_open()) {
        file << s.indexNumber << "," << s.name << endl;
        file.close();
    }
}

// ================= LOAD STUDENTS =================
vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string idx, name;

        getline(ss, idx, ',');
        getline(ss, name);

        students.push_back(Student(idx, name));
    }

    file.close();
    return students;
}

// ================= REGISTER =================
void registerStudent() {
    string idx, name;

    cout << "Enter Index Number: ";
    cin >> idx;

    cout << "Enter Full Name: ";
    cin.ignore();
    getline(cin, name);

    saveStudent(Student(idx, name));

    cout << "Student Registered Successfully!\n";
}

// ================= VIEW =================
void viewStudents() {
    vector<Student> students = loadStudents();

    cout << "\n--- Registered Students ---\n";
    for (size_t i = 0; i < students.size(); i++) {
        cout << students[i].indexNumber
             << " - "
             << students[i].name << endl;
    }
}

// ================= CREATE ATTENDANCE =================
void createAttendance() {

    string courseCode, date;

    cout << "Enter Course Code: ";
    cin >> courseCode;

    cout << "Enter Date (YYYY_MM_DD): ";
    cin >> date;

    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "No students registered!\n";
        return;
    }

    // Create CSV file
    string filename = "session_" + courseCode + "_" + date + ".csv";

    ofstream file(filename.c_str());

    file << "Index Number,Name,Status\n";

    int present = 0, absent = 0, late = 0;
    int choice;
    string status;

    for (size_t i = 0; i < students.size(); i++) {

        cout << "\nMark attendance for "
             << students[i].name << endl;
        cout << "1. Present\n2. Absent\n3. Late\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            status = "Present";
            present++;
        }
        else if (choice == 2) {
            status = "Absent";
            absent++;
        }
        else {
            status = "Late";
            late++;
        }

        // Write to CSV
        file << students[i].indexNumber << ","
             << students[i].name << ","
             << status << endl;
    }

    file.close();

    cout << "\nAttendance saved to: " << filename << endl;

    cout << "\n--- Attendance Summary ---\n";
    cout << "Present: " << present << endl;
    cout << "Absent : " << absent << endl;
    cout << "Late   : " << late << endl;
}

// ================= MAIN MENU =================
int main() {

    int choice;

    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Create Attendance (Generate CSV)\n";
        cout << "4. Exit\n";
        cout << "Choose Option: ";
        cin >> choice;

        switch (choice) {

        case 1:
            registerStudent();
            break;

        case 2:
            viewStudents();
            break;

        case 3:
            createAttendance();
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
