#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

class Student : public Person
{
private:
    int rollno;
    int id;
    char section;
    string subject;
    string course;

public:
    Student();
    Student(string n, int r, int studentId, char sec, string sub, string c);

    void display() override;
    int getRollno();
    int getId();
    char getSection();
    string getSubject();
    string getCourse();

    void setRollno(int r);
    void setId(int studentId);
    void setSection(char sec);
    void setSubject(string sub);
    void setCourse(string c);
};

#endif
