#ifndef SEAT_H
#define SEAT_H

#include "Student.h"

class Seat
{
private:
    int row;
    int column;
    int occupied;
    Student *student;

public:
    Seat();
    Seat(int r, int c);
    int getrow();
    int getcol();
    int getoccupied();
    Student* getStudent();
    void assignStudent(Student *s);
    void clearSeat();
};

#endif
