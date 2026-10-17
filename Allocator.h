#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "StudentManager.h"
#include "RoomManager.h"

class Allocator
{
private:
    int assigned[MAX_STUDENTS];
    int assignedCount;
    int unallocatedCount;

    bool hasConflict(Student *candidate, Room *room, int row, int column);

public:
    Allocator();
    void allocate(StudentManager &studentManager, RoomManager &roomManager);
    void displayUnallocated(StudentManager &studentManager);
    void saveReport(StudentManager &studentManager, RoomManager &roomManager, string fileName);
    bool findStudentSeat(RoomManager &roomManager, int roll, int &roomNo, int &row, int &column);
    int getAssignedCount();
    int getUnallocatedCount();
};

#endif
