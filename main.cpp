#include <iostream>
#include <limits>
#include "StudentManager.h"
#include "RoomManager.h"
#include "Allocator.h"

using namespace std;

void searchStudent(StudentManager &students, Allocator &allocator, RoomManager &rooms, bool allocationDone)
{
    int choice;
    cout << "\n1. Search by roll number\n2. Search by exact name\nChoice: ";
    cin >> choice;

    int index = -1;
    if (choice == 1)
    {
        int roll;
        cout << "Enter roll number: ";
        cin >> roll;
        index = students.findStudent(roll);
    }
    else if (choice == 2)
    {
        string name;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter exact name: ";
        getline(cin, name);
        index = students.findStudent(name);
    }
    else
    {
        cout << "Invalid choice.\n";
        return;
    }

    if (index == -1)
    {
        cout << "Student not found.\n";
        return;
    }

    Student *studentArray = students.getStudents();
    studentArray[index].display();
    if (allocationDone)
    {
        int roomNo, row, column;
        if (allocator.findStudentSeat(rooms, studentArray[index].getRollno(), roomNo, row, column))
            cout << "Room: " << roomNo << ", Row: " << row << ", Column: " << column << endl;
        else
            cout << "This student currently has no allocated seat.\n";
    }
    else
    {
        cout << "Seat location is available after seat allocation.\n";
    }
}

int main()
{
    StudentManager studentManager;
    RoomManager roomManager;
    Allocator allocator;
    bool allocationDone = false;

    if (!studentManager.loadFromFile("students.txt"))
    {
        cout << "Could not open students.txt. Put it in the same folder as the program.\n";
        cout << "Expected format: name|roll|id|section|subject|course\n";
    }
    else
    {
        cout << studentManager.getCount() << " student records loaded from students.txt.\n";
    }

    int choice;
    while (true)
    {
        cout << "\n========== EXAM SEAT ALLOCATOR ==========" << endl;
        cout << "1. Display all students" << endl;
        cout << "2. Add student" << endl;
        cout << "3. Update student" << endl;
        cout << "4. Delete student" << endl;
        cout << "5. Search student" << endl;
        cout << "6. Proceed to seat allocation" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            studentManager.displayAll();
        }
        else if (choice == 2)
        {
            studentManager.addStudent();
            allocationDone = false;
        }
        else if (choice == 3)
        {
            studentManager.updateStudent();
            allocationDone = false;
        }
        else if (choice == 4)
        {
            studentManager.deleteStudent();
            allocationDone = false;
        }
        else if (choice == 5)
        {
            searchStudent(studentManager, allocator, roomManager, allocationDone);
        }
        else if (choice == 6)
        {
            if (studentManager.getCount() == 0)
            {
                cout << "No students available for allocation.\n";
                continue;
            }

            allocator.allocate(studentManager, roomManager);
            allocationDone = true;

            int displayChoice;
            cout << "\n1. Display all rooms\n2. Display one room\nChoice: ";
            cin >> displayChoice;
            if (displayChoice == 1)
            {
                roomManager.displayAllRooms();
            }
            else if (displayChoice == 2)
            {
                int roomNo;
                cout << "Enter room number (1-" << roomManager.getRoomCount() << "): ";
                cin >> roomNo;
                Room *room = roomManager.getRoomByNumber(roomNo);
                if (room != nullptr) room->display();
                else cout << "Invalid room number.\n";
            }
            else
            {
                cout << "Invalid choice.\n";
            }

            allocator.displayUnallocated(studentManager);
            allocator.saveReport(studentManager, roomManager, "seating_output.txt");

            char updateChoice;
            cout << "\nDo you want to return to the management menu to update records? (y/n): ";
            cin >> updateChoice;
            if (updateChoice == 'y' || updateChoice == 'Y')
            {
                // Keep the current seat locations available until records are changed.
                // Add/Update/Delete will mark allocationDone as false.
                continue;
            }
            else
            {
                cout << "Program ended.\n";
                break;
            }
        }
        else if (choice == 0)
        {
            cout << "Program ended.\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
