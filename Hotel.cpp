#include "Hotel.h"

Hotel::Hotel() {
	this->guests = 0;
	this->name = "NONE";
	this->date = Date(2020, 01, 05);

	for (size_t i = 0; i < getNumOfRooms(); i++) {
		this->rooms.push_back(Room(1 + i, 0, 1));
	}

	this->note = "No note given";

	// отвори поток към файла
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

Hotel::~Hotel()
{
	// запазва данните
}

void Hotel::availability() {
	/*cout << "List of free rooms (numbers): " << endl;

	int numOfRooms = getNumOfRooms();
	for (size_t i = 0; i < numOfRooms; i++) {
		if (rooms[i].isFree()) {
			cout << "Room " << rooms[i].getRoomNum() << " | ";
		}
	}*/
}

void Hotel::availability(Period& period) {
	int fromDateYear = period.getFromDateYear();
	int toDateYear = period.getToDateYear();

	if (fromDateYear != 1970 && toDateYear != 1970 && fromDateYear != 0 && toDateYear !=0) {
		if (fromDateYear == toDateYear) {
			cout << "Available room numbers: " << endl;
			int numOfRooms = getNumOfRooms();

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

void Hotel::checkout(int numOfRoom) {
	if (numOfRoom >= 1 && numOfRoom <= 100) {
		if (!(rooms[numOfRoom - 1].isFree())) {
			cout << "Checking out Room " << rooms[numOfRoom - 1].getRoomNum() << "..." << endl;
			rooms[numOfRoom - 1].setAvailability(1);

			int length = rooms[numOfRoom - 1].scheduledDatesSize();
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

void Hotel::checkin(int numOfRoom, Period& period, String& note, int numOfGuests) {
	int fromDateYear = period.getFromDateYear();
	int toDateYear = period.getToDateYear();
	int roomBeds = rooms[numOfRoom - 1].getBeds();

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
	int fromDateYear = period.getFromDateYear();
	int toDateYear = period.getToDateYear();

	if (fromDateYear != 1970 && toDateYear != 1970) {
		if (fromDateYear == toDateYear) {
			cout << "Sending a report..." << endl;
			cout << "Used rooms for a period of " << period.countDaysBetween() << " days" << endl;

			int countFreeRooms = 0;
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

void Hotel::find(int beds, Period period) {
	int fromDateYear = period.getFromDateYear();
	int toDateYear = period.getToDateYear();

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

void Hotel::find_important(int beds, Period period) {
	int fromDateYear = period.getFromDateYear();
	int toDateYear = period.getToDateYear();

	if (fromDateYear != 1970 && toDateYear != 1970) {
		if (fromDateYear == toDateYear) {
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
	}	
}

void Hotel::unavailable(int numOfRoom, Period period, String& note) {
	int fromDateYear = period.getFromDateYear();
	int toDateYear = period.getToDateYear();

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
	int size = 0;

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
