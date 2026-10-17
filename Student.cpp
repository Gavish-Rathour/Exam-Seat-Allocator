#include "Student.h"

Student::Student() : Person()
{
    rollno = 0;
    id = 0;
    section = '-';
    subject = "";
    course = "";
}

Student::Student(string n, int r, int studentId, char sec, string sub, string c)
    : Person(n)
{
    rollno = r;
    id = studentId;
    section = sec;
    subject = sub;
    course = c;
}

void Student::display()
{
    cout << "Name: " << getName() << " | Roll No: " << rollno
         << " | ID: " << id << " | Section: " << section
         << " | Subject: " << subject << " | Course: " << course << endl;
}

int Student::getRollno() { return rollno; }
int Student::getId() { return id; }
char Student::getSection() { return section; }
string Student::getSubject() { return subject; }
string Student::getCourse() { return course; }

void Student::setRollno(int r) { rollno = r; }
void Student::setId(int studentId) { id = studentId; }
void Student::setSection(char sec) { section = sec; }
void Student::setSubject(string sub) { subject = sub; }
void Student::setCourse(string c) { course = c; }
