#include "Seat.h"

Seat::Seat()
{
    row = 0;
    column = 0;
    occupied = 0;
    student = nullptr;
}

Seat::Seat(int r, int c)
{
    row = r;
    column = c;
    occupied = 0;
    student = nullptr;
}

int Seat::getrow() { return row; }
int Seat::getcol() { return column; }
int Seat::getoccupied() { return occupied; }
Student* Seat::getStudent() { return student; }

void Seat::assignStudent(Student *s)
{
    student = s;
    if (s != nullptr) occupied = 1;
    else occupied = 0;
}

void Seat::clearSeat()
{
    student = nullptr;
    occupied = 0;
}
