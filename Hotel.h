#pragma once
#include "Date.h"
#include "Registration.h"
#include "Period.h"
#include "Room.h"

class Hotel {
private:
	String name;
	Vector<Room> rooms;
	int guests;
	Date date;
	String note;
	const int numOfRooms = 100;
	
	bool oneRoomIsReserved = 0;

	void copy(const Hotel& other) {
		this->name = other.name;
		this->rooms = other.rooms;
		this->guests = other.guests;
		this->note = other.note;
	}
public:
	Hotel();
	Hotel(const String name, Vector<Room> rooms, int guests, String note, const Date date);
	Hotel(const Hotel& other);
	Hotel operator= (const Hotel& other);

	// Vector<String> enteredCommand = [checkin, 229, 2020-03-23, 2020-03-31, The, Simpsons, 3]; 
	// etnerdCommand[1] = numOfRoom;
	// enterCommand[2];
	// note = entercommand[4] + entercommand[5];
	
	// Operations
	void availability();
	void availability(Period& period);
	void checkout(int numOfRoom);
	void checkin(int numOfRoom, Period& period, String& note, int numOfGuests);
	void report(Period period);
	void find(int beds, Period period);
	void find_important(int beds, Period period);
	void unavailable(int numOfRoom, Period period, String& note);

	void printRooms();
	void printRoom(int numOfRoom);
	int getNumOfRooms();
	int getRoomNum(int numOfRoom);
};