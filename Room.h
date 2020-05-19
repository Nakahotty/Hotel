#pragma once
#include "String.h"
#include "Vector.h"
#include "Date.h"
#include "Period.h"
#include <iostream>
#include <ctime>

class Room {
private:
	int roomNum;
	int roomGuests;
	bool free;
	int beds;

	void copy(const Room& other) {
		this->roomNum = other.roomNum;
		this->roomGuests = other.roomGuests;
		this->free = other.free;
		this->beds = other.beds;
	}

	Vector<Date> scheduledDates;
public:
	Room();
	Room(const int roomNum, const int RoomGuests, const bool free);
	Room(const Room& other);
	Room operator = (const Room& other);
	void print();

	bool isFree() const;
	void setAvailability(bool free);
	int getRoomNum() const;
	int getRoomGuests() const;
	void addGuests(const int numOfGuests);
	bool isFreeOnDate(Period period);
	int getBeds() const;
	Vector<Date>& getScheduledDates();

	void scheduleOnDates(Period& period);
	int scheduledDatesSize();
	bool isFreeDuringPeriod(Period& period);
};