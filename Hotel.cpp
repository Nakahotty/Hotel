#include "Hotel.h"

Hotel::Hotel() {
	this->guests = 0;
	this->name = "NONE";
	this->date = Date(2020, 01, 05);

	for (size_t i = 0; i < getNumOfRooms(); i++) {
		this->rooms.push_back(Room(1 + i, 0, 1));
	}
	this->note = "No note given";
}

Hotel::Hotel(const String name, Vector<Room> rooms, int guests, String note, const Date date) {
	this->name = name;
	this->rooms = rooms;
	this->guests = guests;
	this->note = note;
	this->date = date;
}

Hotel::Hotel(const Hotel& other)
{
	this->copy(other);
}

Hotel Hotel::operator=(const Hotel& other)
{
	if (this != &other) {
		this->copy(other);
	}

	return *this;
}

void Hotel::availability() {
	cout << "List of free rooms (numbers): " << endl;

	int numOfRooms = getNumOfRooms();
	for (size_t i = 0; i < numOfRooms; i++) {
		if (rooms[i].isFree()) {
			cout << "Room " << rooms[i].getRoomNum() << " | ";
		}
	}
}

void Hotel::availability(Period& period) {
	cout << "Available room numbers: " << endl;
	int numOfRooms = getNumOfRooms();

	if (!oneRoomIsReserved) {
		cout << "All rooms are free!" << endl;
		return;
	}

	cout << "Every room except " << endl;
	for (size_t i = 0; i < numOfRooms; i++) {
		if (!rooms[i].isFreeOnDate(period))
			cout << rooms[i].getRoomNum() << " ";
	}
}

void Hotel::checkout(int numOfRoom) {
	if (!(rooms[numOfRoom - 1].isFree())) {
		cout << "Checking out Room " << rooms[numOfRoom - 1].getRoomNum() << "..." << endl;
		rooms[numOfRoom - 1].setAvailability(1);
	}
	else {
		cout << "Room " << rooms[numOfRoom - 1].getRoomNum() << " is already free." << endl;
	}
}

void Hotel::checkin(int numOfRoom, Period& period, String& note, int numOfGuests) {
	cout << "Checking in " << numOfGuests << " guests in room " << numOfRoom << endl;
	rooms[numOfRoom - 1].scheduleOnDates(period);
	rooms[numOfRoom - 1].addGuests(numOfGuests);
	cout << "Note - " << note << endl;

	oneRoomIsReserved = 1;
}

void Hotel::report(Period period)
{
	cout << "Sending a report..." << endl;
	cout << "Used rooms for a period of " << period.countDaysBetween() << " days"<< endl;

	int countFreeRooms = 0;
	for (size_t i = 0; i < period.countDaysBetween(); i++) {
		if (rooms[i].scheduledDatesSize() == 0) {
			countFreeRooms++;
			continue;
		}

		if (!(rooms[i].isFreeDuringPeriod(period))) {
			rooms[i].print();
		}
	}

	if (countFreeRooms == period.countDaysBetween()) {
		cout << "There are no used rooms in that period!" << endl;
	}
}

void Hotel::find(int beds, Period period) {
	cout << "Finding a room with " << beds << " beds...";

	for (size_t i = 0; i < numOfRooms; i++) {
		if (rooms[i].getBeds() == beds && rooms[i].isFreeDuringPeriod(period)) {
			cout << "We found a room for you!" << endl;
			rooms[i].print();
			return;
		}
	}

	cout << "Sorry, we do not have an available room with " << beds << " beds." << endl;
}

void Hotel::find_important(int beds, Period period) {
	cout << "Finding a room for an important person..." << endl;
	
	int foundRoomIndex = 0;

	for (size_t i = 0; i < numOfRooms; i++) {
		if (rooms[i].getBeds() == beds) {
			foundRoomIndex = i;

			if (rooms[i].isFreeDuringPeriod(period)) {
				cout << "We found a free room for you!" << endl;
				rooms[i].print();
				return;
			}
		}
	}

	for (size_t j = foundRoomIndex + 1; j < numOfRooms; j++) {
		if (rooms[j].isFreeDuringPeriod(period) && rooms[j].getBeds() == beds) {
			rooms[j] = rooms[foundRoomIndex];
			rooms[j].setAvailability(0);
			cout << "We have cleared a room for the special guest!" << endl;
			rooms[foundRoomIndex].print();
			return;
		}
	}
}

void Hotel::unavailable(int numOfRoom, Period period, String& note) {
	rooms[numOfRoom - 1].scheduleOnDates(period);
	cout << "This room is currently unavailable." << endl;
	cout << "Note - " << note << endl;
}

void Hotel::printRooms() {
	for (size_t i = 0; i < this->getNumOfRooms(); i++) {
		rooms[i].print();
	}
}

void Hotel::printRoom(int numOfRoom) {
	rooms[numOfRoom - 1].print();
	cout << endl;
}


int Hotel::getNumOfRooms() {
	return this->numOfRooms;
}

int Hotel::getRoomNum(int numOfRoom)
{
	return rooms[numOfRoom-1].getRoomNum();
}
