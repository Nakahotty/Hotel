#pragma once
#include "Date.h"
#include "Period.h"
#include "Room.h"

class Hotel {
private:
	String name;
	Vector<Room> rooms;
	size_t guests;
	Date date;
	String note;
	const size_t numOfRooms = 100;

	bool oneRoomIsReserved = 0;

	void copy(const Hotel& other) {
		this->name = other.name;
		this->rooms = other.rooms;
		this->note = other.note;
	}

	// ifstream& in;
	// ofstream& out;

public:
	Hotel();
	Hotel(const String name, Vector<Room> rooms, size_t guests, String note, const Date date);
	Hotel(const Hotel& other);
	Hotel operator= (const Hotel& other);

	// Operations
	void availability();
	void availability(Period& period);
	void checkout(size_t numOfRoom);
	void checkin(size_t numOfRoom, Period& period, String& note, size_t numOfGuests);
	void report(Period period);
	void find(size_t beds, Period period);
	void find_important(size_t beds, Period period);
	void unavailable(size_t numOfRoom, Period period, String& note);

	void printRooms();
	void printRoom(size_t numOfRoom);
	size_t getNumOfRooms();
	size_t getRoomNum(size_t numOfRoom);
	void setOneRoomReserved(bool resereved);
	ofstream& saveHotel(ofstream& out) const;
	ifstream& loadHotel(ifstream& in);
};