#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"

const int MAX_STUDENTS = 500;

class StudentManager
{
private:
    Student students[MAX_STUDENTS];
    int count;

public:
    StudentManager();
    bool loadFromFile(string fileName);
    int getCount();
    Student* getStudents();
    void displayAll();
    int findStudent(int rollno);
    int findStudent(string name);
    void addStudent();
    void updateStudent();
    void deleteStudent();
};

#endif
