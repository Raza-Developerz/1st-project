# 1st-project
Student management system.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Student 
{
 public:
    int roll;
    string name;
    float marks;
    string course;

    void input()
     {
        cout << "Enter Roll No: ";
        cin >> roll;
        cin.ignore(); // buffer clear
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Course: ";
        getline(cin, course);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display()
     {
        cout << "\n--------------------------\n";
        cout << "Roll No : " << roll << endl;
        cout << "Name : " << name << endl;
        cout << "Course : " << course << endl;
        cout << "Marks : " << marks << endl;
        cout << "--------------------------\n";
    }
}
// File me save karna
void saveToFile(vector<Student> &students)
{
    ofstream fout("students.txt");
    for(auto s : students) {
        fout << s.roll << "," << s.name << "," << s.course << "," << s.marks << "\n";
    }
    fout.close();
}
// File se load karna
void loadFromFile(vector<Student> &students) {
    ifstream fin("students.txt");
    Student s;
    char comma;
    while(fin >> s.roll) {
        fin >> comma;
        getline(fin, s.name, ',');
        getline(fin, s.course, ',');
        fin >> s.marks;
        fin.ignore();
        students.push_back(s);
    }
    fin.close();
}
void addStudent(vector<Student> &students) {
    Student s;
    s.input();
    students.push_back(s);
    saveToFile(students);
    cout << "\nStudent Added Successfully!\n";
}
void displayAll(vector<Student> &students) {
    if(students.empty()) {
        cout << "No Records Found!\n";
        return;
    }
    for(auto s : students) {
        s.display();
    }
}

void searchStudent(vector<Student> &students) {
    int r;
    cout << "Enter Roll No to Search: ";
    cin >> r;
    for(auto s : students) {
        if(s.roll == r) {
            s.display();
            return;
        }
    }
    cout << "Student Not Found!\n";
}

void deleteStudent(vector<Student> &students) {
    int r;
    cout << "Enter Roll No to Delete: ";
    cin >> r;
    for(int i=0; i<students.size(); i++)
     {
        if(students[i].roll == r) {
            students.erase(students.begin() + i);
            saveToFile(students);
            cout << "Student Deleted Successfully!\n";
            return;
        }
    }
    cout << "Student Not Found!\n";
}

void updateStudent(vector<Student> &students) {
    int r;
    cout << "Enter Roll No to Update: ";
    cin >> r;
    for(auto &s : students) {
        if(s.roll == r) {
            cout << "Enter New Data:\n";
            s.input();
            saveToFile(students);
            cout << "Student Updated Successfully!\n";
            return;
        }
    }
    cout << "Student Not Found!\n";
}

int main() {
    vector<Student> students;
    loadFromFile(students); // pehle wale data load kar lo
    int choice;

    do {
        cout << "\n====== STUDENT MANAGEMENT SYSTEM ======\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addStudent(students); break;
            case 2: displayAll(students); break;
            case 3: searchStudent(students); break;
            case 4: updateStudent(students); break;
            case 5: deleteStudent(students); break;
            case 6: cout << "Exiting... Bye!\n"; break;
            default: cout << "Invalid Choice!\n";
        }
    } while(choice!= 6);

    return 0;
}
