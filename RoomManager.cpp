#include "RoomManager.h"

RoomManager::RoomManager()
{
    roomCount = MAX_ROOMS;
    for (int i = 0; i < roomCount; i++)
        rooms[i] = Room(i + 1);
}

int RoomManager::getRoomCount() { return roomCount; }
Room* RoomManager::getRooms() { return rooms; }

Room* RoomManager::getRoomByNumber(int roomNumber)
{
    for (int i = 0; i < roomCount; i++)
        if (rooms[i].getRoomNumber() == roomNumber) return &rooms[i];
    return nullptr;
}

void RoomManager::displayAllRooms()
{
    for (int i = 0; i < roomCount; i++)
        rooms[i].display();
}
