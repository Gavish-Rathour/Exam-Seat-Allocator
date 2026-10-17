#ifndef ROOM_H
#define ROOM_H

#include "Seat.h"

const int ROOM_ROWS = 10;
const int ROOM_COLS = 10;

class Room
{
private:
    int roomNumber;
    int rows;
    int columns;
    Seat seats[ROOM_ROWS][ROOM_COLS];

public:
    Room();
    Room(int number);
    int getRoomNumber();
    int getRows();
    int getColumns();
    Seat* getSeat(int row, int column);
    void clearRoom();
    void display();
};

#endif
