#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student {
    int rollNo;
    char name[100];
    float marks;
};

// Function to add student
void addStudent() {
    ofstream file("students.dat", ios::binary | ios::app);
    Student s;
    cout << "\nEnter Roll No: ";
    cin >> s.rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(s.name, 50);
    cout << "Enter Marks: ";
    cin >> s.marks;
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Student record added successfully!\n";
}

// Function to display all students
void displayStudents() {
    ifstream file("students.dat", ios::binary);
    Student s;
    cout << "\n--- Student Records ---\n";
    while (file.read((char*)&s, sizeof(s))) {
        cout << "Roll No: " << s.rollNo << "\nName: " << s.name << "\nMarks: " << s.marks << "\n\n";
    }
    file.close();
}

// Function to search student by roll number
void searchStudent(int roll) {
    ifstream file("students.dat", ios::binary);
    Student s;
    bool found = false;
    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "\nRecord Found!\n";
            cout << "Roll No: " << s.rollNo << "\nName: " << s.name << "\nMarks: " << s.marks << "\n";
            found = true;
            break;
        }
    }
    file.close();
    if (!found) cout << "\nStudent not found!\n";
}

// Function to delete student
void deleteStudent(int roll) {
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    Student s;
    bool found = false;
    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo != roll) {
            temp.write((char*)&s, sizeof(s));
        }
        else {
            found = true;
        }
    }
    file.close();
    temp.close();
    remove("students.dat");
    rename("temp.dat", "students.dat");
    if (found) cout << "Student deleted successfully!\n";
    else cout << "Student not found!\n";
}

// Function to update student
void updateStudent(int roll) {
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    Student s;
    bool found = false;
    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "Enter new name: ";
            cin.ignore();
            cin.getline(s.name, 50);
            cout << "Enter new marks: ";
            cin >> s.marks;
            int pos = -1 * (int)sizeof(s);
            file.seekp(pos, ios::cur);
            file.write((char*)&s, sizeof(s));
            found = true;
            cout << "Record updated successfully!\n";
            break;
        }
    }
    file.close();
    if (!found) cout << "Student not found!\n";
}

int main() {
    // Clear old file (only for testing)
    ofstream clearFile("students.dat", ios::binary | ios::trunc);
    clearFile.close();
    int choice, roll;
    while (true) {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n2. Display Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayStudents(); break;
        case 3: cout << "Enter Roll No to search: "; cin >> roll; searchStudent(roll); break;
        case 4: cout << "Enter Roll No to update: "; cin >> roll; updateStudent(roll); break;
        case 5: cout << "Enter Roll No to delete: "; cin >> roll; deleteStudent(roll); break;
        case 6: exit(0);
        default: cout << "Please Enter valid choice\n";
        }
    }
    return 0;
}
