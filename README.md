Student Management System — C
A console-based Student Management System written in pure C, built as part of my C programming coursework. The system manages student records at runtime using a singly linked list with full CRUD operations, GPA analytics, and robust input validation.

Features
#FeatureDescription1Add StudentInsert a new student record (ID, name, age, GPA) with duplicate ID detection2Display AllPrint all student records stored in the linked list3Search by IDLocate and display a specific student by their unique ID4Update RecordModify name, age, or GPA of an existing student5Delete RecordRemove a student from the list and free allocated memory6Average GPACalculate and display the average GPA across all students7Highest GPAFind and display the student with the top GPA

Data Structure
The project uses a singly linked list where each node holds a student struct:
cstruct student {
    int   id;
    char  name[64];
    int   age;
    float gpa;
};

struct node {
    struct student data;
    struct node   *next;
};

Concepts Demonstrated

Dynamic memory allocation (malloc, free)
Singly linked list traversal, insertion, and deletion
Struct-based data modeling
Input validation and stdin flushing
Modular design with static helper functions
Safe string handling (fgets, strncpy, strcspn)
assert() for development-time memory checks


Build & Run
Requirements

GCC or any C99-compatible compiler
Works on Windows, Linux, and macOS

Compile
bashgcc -Wall -Wextra -std=c99 -o student_system project.c
Run
bash./student_system
Sample Interaction
--- Student Management System ---
1. Add a Student
2. Display All Students
3. Search for a Student by ID
4. Update Student Information
5. Delete a Student
6. Calculate Average GPA
7. Find Student with Highest GPA
8. Exit
Choose an option: 1

Enter student ID: 101
Enter name: Mohamed Baiomy
Enter age: 20
Enter GPA: 3.85
Student added successfully.

Project Structure
project/
├── project.c       # Main source file (all logic)
├── Debug/
│   ├── project.exe # Compiled executable (Windows)
│   └── project.o   # Object file
└── README.md

Author
Mohamed Baiomy Abdelkader
Mechatronics & Robotics Engineering Student — Ain Shams University
LinkedIn · GitHub
