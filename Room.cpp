#include "Room.h"
#include <stdlib.h>
#include <time.h>

Room::Room() {
	this->roomNum = 1;
	this->roomGuests = 0;
	this->free = 1;
	this->beds = rand() % 5 + 1;
}

Room::Room(const int roomNum, const int roomGuests, const bool free) {
	this->roomNum = roomNum;
	this->roomGuests = roomGuests;
	this->free = free;
	this->beds = rand() % 5 + 1;
}

Room::Room(const Room& other) {
	this->copy(other);
}

Room Room::operator=(const Room& other) {
	if (this != &other) {
		this->copy(other);
	}

	return *this;
}

void Room::print() {
	cout << "Room number: " << roomNum << endl;
	cout << "Guests: " << roomGuests << endl;
	cout << "Is free: " << free << endl;
	cout << "Beds: " << beds << endl;
}

bool Room::isFree() const
{
	return this->free;
}

void Room::setAvailability(bool availability)
{
	this->free = availability;
}

int Room::getRoomNum() const
{
	return this->roomNum;
}

int Room::getRoomGuests() const
{
	return this->roomGuests;
}

void Room::addGuests(const int numOfGuests){
	this->roomGuests += numOfGuests;
}

bool Room::isFreeOnDate(Period period)
{
	Date date = period.getDate();
	int size = scheduledDates.getSize();

	for (int i = 0; i < size; i++) {
		if (date == scheduledDates[i]) {
			return false;
		}
	}

	return true;
}

int Room::getBeds() const
{
	return this->beds;
}

void Room::scheduleOnDates(Period& period)
{
	if (!isFreeDuringPeriod(period)) {
		cout << "The room is taken during this period!" << endl;
		return;
	}

	Vector<Date> dates = period.getDatesInPeriod();
	int daysBetweenPeriod = period.countDaysBetween();

	for (size_t i = 0; i < daysBetweenPeriod; i++) {
		this->scheduledDates.push_back(dates[i]);
		dates[i].print();
	}

	this->setAvailability(0);
}

int Room::scheduledDatesSize()
{
	return scheduledDates.getSize();
}


bool Room::isFreeDuringPeriod(Period& period)
{
	Vector<Date> dates = period.getDatesInPeriod();

	for (size_t i = 0; i < dates.getSize(); i++) {
		if (scheduledDates.contains(dates[i]))
			return false;
	}

	return true;
}

