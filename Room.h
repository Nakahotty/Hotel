#pragma once
#include "String.h"
#include "Vector.h"
#include "Date.h"
#include "Period.h"
#include <iostream>
#include <ctime>

class Room {
private:
	size_t roomNum;
	size_t roomGuests;
	bool free;
	size_t beds;
	Vector<Date> scheduledDates;

	void copy(const Room& other) {
		this->roomNum = other.roomNum;
		this->roomGuests = other.roomGuests;
		this->free = other.free;
		this->beds = other.beds;
		this->scheduledDates = other.scheduledDates;
	}
public:
	Room();
	Room(const size_t roomNum, const size_t RoomGuests, const bool free);
	Room(const Room& other);
	Room operator = (const Room& other);
	void print();

	bool isFree() const;
	void setAvailability(bool free);
	size_t getRoomNum() const;
	size_t getRoomGuests() const;
	void addGuests(const int numOfGuests);
	bool isFreeOnDate(Period period);
	size_t getBeds() const;
	Vector<Date>& getScheduledDates();

	void scheduleOnDates(Period& period);
	size_t scheduledDatesSize();
	bool isFreeDuringPeriod(Period& period);

	ofstream& saveScheduledDates(ofstream& out) const;
	ifstream& loadScheduledDates(ifstream& in);

	ofstream& saveRoom(ofstream& out) const;
	ifstream& loadRoom(ifstream& in);
};