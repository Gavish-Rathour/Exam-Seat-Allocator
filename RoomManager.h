#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include "Room.h"

const int MAX_ROOMS = 5;

class RoomManager
{
private:
    Room rooms[MAX_ROOMS];
    int roomCount;

public:
    RoomManager();
    int getRoomCount();
    Room* getRooms();
    Room* getRoomByNumber(int roomNumber);
    void displayAllRooms();
};

#endif
