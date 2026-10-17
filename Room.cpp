#include "Room.h"
#include <iomanip>

Room::Room()
{
    roomNumber = 0;
    rows = ROOM_ROWS;
    columns = ROOM_COLS;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            seats[r][c] = Seat(r + 1, c + 1);
}

Room::Room(int number)
{
    roomNumber = number;
    rows = ROOM_ROWS;
    columns = ROOM_COLS;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            seats[r][c] = Seat(r + 1, c + 1);
}

int Room::getRoomNumber() { return roomNumber; }
int Room::getRows() { return rows; }
int Room::getColumns() { return columns; }

Seat* Room::getSeat(int row, int column)
{
    if (row < 0 || row >= rows || column < 0 || column >= columns)
        return nullptr;
    return &seats[row][column];
}

void Room::clearRoom()
{
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < columns; c++)
            seats[r][c].clearSeat();
}

void Room::display()
{
    cout << "\n========== ROOM " << roomNumber << " ==========\n";
    cout << "Roll numbers (---- means empty seat)\n\n";
    cout << setw(6) << "Row";
    for (int c = 0; c < columns; c++) cout << setw(7) << c + 1;
    cout << endl;

    for (int r = 0; r < rows; r++)
    {
        cout << setw(6) << r + 1;
        for (int c = 0; c < columns; c++)
        {
            Student *s = seats[r][c].getStudent();
            if (s != nullptr) cout << setw(7) << s->getRollno();
            else cout << setw(7) << "----";
        }
        cout << endl;
    }
}
