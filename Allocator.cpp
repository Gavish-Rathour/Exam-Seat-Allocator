#include "Allocator.h"
#include <fstream>

Allocator::Allocator()
{
    assignedCount = 0;
    unallocatedCount = 0;
    for (int i = 0; i < MAX_STUDENTS; i++) assigned[i] = 0;
}

bool Allocator::hasConflict(Student *candidate, Room *room, int row, int column)
{
    // Check only left and upper seats. Right and lower seats will be checked later.
    if (column > 0)
    {
        Student *left = room->getSeat(row, column - 1)->getStudent();
        if (left != nullptr)
        {
            if (left->getSubject() == candidate->getSubject() ||
                left->getSection() == candidate->getSection()) return true;
        }
    }

    if (row > 0)
    {
        Student *upper = room->getSeat(row - 1, column)->getStudent();
        if (upper != nullptr)
        {
            if (upper->getSubject() == candidate->getSubject() ||
                upper->getSection() == candidate->getSection()) return true;
        }
    }
    return false;
}

void Allocator::allocate(StudentManager &studentManager, RoomManager &roomManager)
{
    Room *rooms = roomManager.getRooms();
    Student *students = studentManager.getStudents();
    int studentCount = studentManager.getCount();

    for (int i = 0; i < MAX_STUDENTS; i++) assigned[i] = 0;
    assignedCount = 0;
    unallocatedCount = 0;

    for (int r = 0; r < roomManager.getRoomCount(); r++) rooms[r].clearRoom();

    // Greedy allocation: each empty seat gets the first unassigned compatible student.
    for (int roomIndex = 0; roomIndex < roomManager.getRoomCount(); roomIndex++)
    {
        for (int row = 0; row < ROOM_ROWS; row++)
        {
            for (int col = 0; col < ROOM_COLS; col++)
            {
                bool seatFilled = false;
                for (int i = 0; i < studentCount; i++)
                {
                    if (assigned[i] == 0 &&
                        !hasConflict(&students[i], &rooms[roomIndex], row, col))
                    {
                        rooms[roomIndex].getSeat(row, col)->assignStudent(&students[i]);
                        assigned[i] = 1;
                        assignedCount++;
                        seatFilled = true;
                        break;
                    }
                }
                (void)seatFilled;
            }
        }
    }

    unallocatedCount = studentCount - assignedCount;
    cout << "\nSeat allocation finished.\n";
    cout << "Total students: " << studentCount << endl;
    cout << "Allocated students: " << assignedCount << endl;
    cout << "Unallocated students: " << unallocatedCount << endl;
}

void Allocator::displayUnallocated(StudentManager &studentManager)
{
    if (unallocatedCount == 0)
    {
        cout << "All students have been allocated.\n";
        return;
    }

    cout << "\nStudents not allocated a seat:\n";
    Student *students = studentManager.getStudents();
    int count = studentManager.getCount();
    for (int i = 0; i < count; i++)
        if (assigned[i] == 0) students[i].display();
}

void Allocator::saveReport(StudentManager &studentManager, RoomManager &roomManager, string fileName)
{
    ofstream fout(fileName.c_str()); // Opens in overwrite mode, not append mode.
    if (!fout)
    {
        cout << "Could not open output file.\n";
        return;
    }

    fout << "EXAM SEAT ALLOCATION REPORT\n";
    fout << "Total students: " << studentManager.getCount() << endl;
    fout << "Allocated students: " << assignedCount << endl;
    fout << "Unallocated students: " << unallocatedCount << endl;

    Room *rooms = roomManager.getRooms();
    for (int i = 0; i < roomManager.getRoomCount(); i++)
    {
        fout << "\nROOM " << rooms[i].getRoomNumber() << "\n";
        fout << "Roll numbers; ---- means empty seat\n";
        for (int r = 0; r < ROOM_ROWS; r++)
        {
            for (int c = 0; c < ROOM_COLS; c++)
            {
                Student *s = rooms[i].getSeat(r, c)->getStudent();
                if (s != nullptr) fout << s->getRollno();
                else fout << "----";
                if (c < ROOM_COLS - 1) fout << '\t';
            }
            fout << endl;
        }
    }

    fout << "\nUNALLOCATED STUDENTS\n";
    Student *students = studentManager.getStudents();
    for (int i = 0; i < studentManager.getCount(); i++)
        if (assigned[i] == 0)
            fout << students[i].getRollno() << " | " << students[i].getName() << endl;

    fout.close();
    cout << "Seating arrangement saved to " << fileName << endl;
}

bool Allocator::findStudentSeat(RoomManager &roomManager, int roll, int &roomNo, int &row, int &column)
{
    Room *rooms = roomManager.getRooms();
    for (int i = 0; i < roomManager.getRoomCount(); i++)
    {
        for (int r = 0; r < ROOM_ROWS; r++)
        {
            for (int c = 0; c < ROOM_COLS; c++)
            {
                Student *s = rooms[i].getSeat(r, c)->getStudent();
                if (s != nullptr && s->getRollno() == roll)
                {
                    roomNo = rooms[i].getRoomNumber();
                    row = r + 1;
                    column = c + 1;
                    return true;
                }
            }
        }
    }
    return false;
}

int Allocator::getAssignedCount() { return assignedCount; }
int Allocator::getUnallocatedCount() { return unallocatedCount; }
