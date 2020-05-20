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

Vector<Date>& Room::getScheduledDates() 
{
	return this->scheduledDates;
}

void Room::scheduleOnDates(Period& period)
{
	if (!isFreeDuringPeriod(period)) {
		cout << "The room is taken during this period!" << endl;
		return;
	} 

	Vector<Date> dates = period.getDatesInPeriod();
	int daysBetweenPeriod = period.countDaysBetween();

	for (size_t i = 0; i <= daysBetweenPeriod; i++) {
		this->scheduledDates.push_back(dates[i]);
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
	int length = period.countDaysBetween();

	for (size_t i = 0; i < length; i++) {
		if (scheduledDates.contains(dates[i]))
			return false;
	}

	return true;
}

ofstream& Room::saveScheduledDates(ofstream& out) const
{
	int size = scheduledDates.getSize();

	for (size_t i = 0; i < size; i++) {
		scheduledDates[i].saveDate(out);
	}

	return out;
}

ifstream& Room::loadScheduledDates(ifstream& in)
{
	int size = scheduledDates.getSize();

	for (size_t i = 0; i < size; i++) {
		scheduledDates[i].loadDate(in);
	}

	return in;
}

ofstream& Room::saveRoom(ofstream& out) const
{
	int size = scheduledDates.getSize();

	out << "Room number: " << roomNum << endl;
	out << "Guests: " << roomGuests << endl;
	out << "Is free: " << free << endl;
	out << "Beds: " << beds << endl;
	out << "Scheduled dates: " << size << endl;

	for (size_t i = 0; i < size; i++) {
		scheduledDates[i].saveDate(out);
	}

	return out;
}

ifstream& Room::loadRoom(ifstream& in)
{
	int size = 0;

	in.seekg(13, ios::cur); // for room number
	in >> roomNum;
	in.seekg(9, ios::cur); // for guests
	in >> roomGuests;
	in.seekg(10, ios::cur); // for free
	in >> free;
	in.seekg(7, ios::cur); // for beds
	in >> beds;
	in.seekg(18, ios::cur); // for scheduled dates
	in >> size;
	in.seekg(2, ios::cur); // for endline

	for (int i = 0; i < size; i++) {
		if (i == 0) {
			Date date;
			date.loadDate(in);
			this->scheduledDates.push_back(date);
		}
		else {
			in.seekg(2, ios::cur);
			Date date;
			date.loadDate(in);
			this->scheduledDates.push_back(date);
		}

		if (i == (size - 1)) {
			in.seekg(2, ios::cur);
		}
	}


	return in;
}

