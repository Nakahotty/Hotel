#include "Hotel.h"

Hotel::Hotel() {
	this->guests = 0;
	this->name = "Àtanas++";
	this->date = Date(2020, 01, 05);

	for (size_t i = 0; i < getNumOfRooms(); i++) {
		this->rooms.push_back(Room(1 + i, 0, 1));
	}

	this->note = "No note given";
}

Hotel::Hotel(const String name, Vector<Room> rooms, size_t guests, String note, const Date date) {
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
	
}

void Hotel::availability(Period& period) {
	size_t fromDateYear = period.getFromDateYear();
	size_t toDateYear = period.getToDateYear();

	if (fromDateYear != 1970 && toDateYear != 1970 && fromDateYear != 0 && toDateYear != 0) {
		if (fromDateYear == toDateYear) {
			cout << "Available room numbers: " << endl;
			size_t numOfRooms = getNumOfRooms();

			/*if (!oneRoomIsReserved) {
				cout << "All rooms are free!" << endl;
				return;
			}*/

			cout << "Every room except " << endl;
			for (size_t i = 0; i < numOfRooms; i++) {
				if (!rooms[i].isFreeOnDate(period))
					cout << rooms[i].getRoomNum() << " ";
			}

			cout << endl;
		}
	}


}

void Hotel::checkout(size_t numOfRoom) {
	if (numOfRoom >= 1 && numOfRoom <= 100) {
		if (!(rooms[numOfRoom - 1].isFree())) {
			cout << "Checking out Room " << rooms[numOfRoom - 1].getRoomNum() << "..." << endl;
			rooms[numOfRoom - 1].setAvailability(1);

			size_t length = rooms[numOfRoom - 1].scheduledDatesSize();
			for (size_t i = 0; i < length; i++) {
				rooms[numOfRoom - 1].getScheduledDates().pop_back();
			}

			oneRoomIsReserved = 0;
		}
		else {
			cout << "Room " << rooms[numOfRoom - 1].getRoomNum() << " is already free." << endl;
		}
	}
	else {
		cout << "Enter a valid room number!" << endl;
	}


}

void Hotel::checkin(size_t numOfRoom, Period& period, String& note, size_t numOfGuests) {
	size_t fromDateYear = period.getFromDateYear();
	size_t toDateYear = period.getToDateYear();
	size_t roomBeds = rooms[numOfRoom - 1].getBeds();

	if (fromDateYear != 1970 && toDateYear != 1970) {
		if (fromDateYear == toDateYear) {
			if (numOfGuests >= 1 && numOfGuests <= roomBeds) {
				cout << "Checking in " << numOfGuests << " guests in room " << numOfRoom << endl;
				rooms[numOfRoom - 1].scheduleOnDates(period);
				rooms[numOfRoom - 1].addGuests(numOfGuests);
				cout << "Note - " << note << endl;

				oneRoomIsReserved = 1;
			}
			else {
				cout << "Invalid number of guests! (This room has " << roomBeds << " beds)" << endl;
			}
		}
	}
}


void Hotel::report(Period period)
{
	size_t fromDateYear = period.getFromDateYear();
	size_t toDateYear = period.getToDateYear();

	if (fromDateYear != 1970 && toDateYear != 1970) {
		if (fromDateYear == toDateYear) {
			cout << "Sending a report..." << endl;
			cout << "Used rooms for a period of " << period.countDaysBetween() << " days" << endl;

			size_t countFreeRooms = 0;
			for (size_t i = 0; i < numOfRooms; i++) {
				if (rooms[i].scheduledDatesSize() == 0) {
					countFreeRooms++;
				}

				if (!(rooms[i].isFreeDuringPeriod(period))) {
					rooms[i].print();
				}
			}

			if (countFreeRooms == period.countDaysBetween()) {
				cout << "There are no used rooms in that period!" << endl;
			}
		}
	}

}

void Hotel::find(size_t beds, Period period) {
	size_t fromDateYear = period.getFromDateYear();
	size_t toDateYear = period.getToDateYear();

	if (fromDateYear != 1970 && toDateYear != 1970) {
		if (fromDateYear == toDateYear) {
			cout << "Finding a room with " << beds << " beds..." << endl;

			for (size_t i = 0; i < numOfRooms; i++) {
				if (rooms[i].getBeds() == beds && rooms[i].isFreeDuringPeriod(period)) {
					cout << "We found a room for you!" << endl;
					rooms[i].print();
					return;
				}
			}

			cout << "Sorry, we do not have an available room with " << beds << " beds." << endl;
		}
	}

}

void Hotel::find_important(size_t beds, Period period) {
	size_t fromDateYear = period.getFromDateYear();
	size_t toDateYear = period.getToDateYear();

	if (fromDateYear != 1970 && toDateYear != 1970) {
		if (fromDateYear == toDateYear) {
			cout << "Finding a room for an important person..." << endl;

			size_t foundRoomIndex = 0;

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
	}
}

void Hotel::unavailable(size_t numOfRoom, Period period, String& note) {
	size_t fromDateYear = period.getFromDateYear();
	size_t toDateYear = period.getToDateYear();

	if (fromDateYear != 1970 && toDateYear != 1970) {
		if (fromDateYear == toDateYear) {
			if (rooms[numOfRoom - 1].isFreeDuringPeriod(period)) {
				rooms[numOfRoom - 1].scheduleOnDates(period);
				cout << "Setting room " << numOfRoom << " for unavailable..." << endl;
				cout << "Note - " << note << " (limited to one word)" << endl;
			}
			else {
				cout << "Room " << numOfRoom << " is already unavailable!" << endl;
			}
		}
	}

}

void Hotel::printRooms() {
	for (size_t i = 0; i < this->getNumOfRooms(); i++) {
		rooms[i].print();
	}
}

void Hotel::printRoom(size_t numOfRoom) {
	rooms[numOfRoom - 1].print();
	cout << endl;
}


size_t Hotel::getNumOfRooms() {
	return this->numOfRooms;
}

size_t Hotel::getRoomNum(size_t numOfRoom)
{
	return rooms[numOfRoom - 1].getRoomNum();
}

void Hotel::setOneRoomReserved(bool reserved)
{
	this->oneRoomIsReserved = reserved;
}


ofstream& Hotel::saveHotel(ofstream& out) const
{
	out << "Hotel " << this->name << endl;
	out << "Rooms: " << this->numOfRooms << endl << endl;

	for (size_t i = 0; i < this->numOfRooms; i++) {
		this->rooms[i].saveRoom(out);
	}

	return out;
}

ifstream& Hotel::loadHotel(ifstream& in)
{
	// For the num of rooms
	size_t size = 0;

	in.seekg(6, ios::cur);
	in >> name;
	in.seekg(7, ios::cur);
	in >> size;
	in.seekg(2, ios::cur);

	for (size_t i = 0; i < size; i++) {
		if (i == 0) {
			in.seekg(2, ios::cur);
			Room room;
			room.loadRoom(in);
			this->rooms[i] = room;
		}
		else {
			Room room;
			room.loadRoom(in);
			this->rooms[i] = room;
		}
	}


	return in;
}
