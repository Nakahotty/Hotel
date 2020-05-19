#include "ConsoleEngine.h"

void ConsoleEngine::run() {
	bool exited = 0;
	Hotel hotel;
	int numOfRoom, numOfGuests = 0; 
	String note;
	Period period;
	String periodString;
	int year1, day1, month1, year2, day2, month2 = 0;
	String date1String, date2String;
	Date date1, date2;
	int beds = 0;

	ofstream out;
	ifstream in;

	do {
		cin >> cmd;
		Vector<String> arguments = split(cmd);

		switch (checkOperation(cmd)) {
		case 1:
			// Open
			if (arguments.getSize() > 1 && !(arguments[1] == '\0')) {
				String fileName = arguments[1];

				if (in.is_open() || out.is_open()) {
					cout << "File already opened!" << endl;
				}
				else {
					out.open(fileName.c_str(), ios::app);
					in.open(fileName.c_str());

					if (!(is_empty(in))) {
						hotel.loadHotel(in);
					}
					else {
						hotel.saveHotel(out);
					}

					in.close();

					if (out.is_open()) {
						cout << "Opening file " << fileName << "..." << endl;
					}
				}
			}
			else {
				cout << "Missing arguments!" << endl;
			}

			break;
		case 2:
			// Close
			if (arguments.getSize() > 1 && !(arguments[1] == '\0')) {
				String fileName = arguments[1];

				// нулирай хотела
				if (out.is_open()) {
					cout << "Closing file " << fileName << "..." << endl;
					out.close();
				}
				else {
					cout << "No file is opened!" << endl;
				}

			}
			else {
				cout << "Missing arguments!" << endl;
			}

			break;
		case 3:
			// Save
			if (arguments.getSize() > 1 && !(arguments[1] == '\0')) {
				String fileName = arguments[1];

				if (out.is_open()) {
					cout << "Saving file..." << endl;
					out.close();
					out.open(fileName.c_str(), ios::trunc);

					hotel.saveHotel(out);
				}
				else {
					cout << "No file is opened" << endl;
				}
				
			}
			else {
				cout << "Missing arguments!" << endl;
			}
			
			break;
		case 4:
			// Save as
			if (arguments.getSize() > 1 && !(arguments[1] == '\0')) {
				cout << "Saving file as..." << endl;
			}
			else {
				cout << "Missing arguments!" << endl;
			}

			break;
		case 5:
			// Help
			cout << "The following commands are supported: " << endl;
			cout << "open <file> - Opens <file>" << endl;
			cout << "close - Closes currently oppened file" << endl;
			cout << "save - Saves the currently oppened file" << endl;
			cout << "saveas <file> - Saves the currently oppened file in <file>" << endl;
			cout << "help - Prints this information" << endl;
			cout << "exit - Exits the program" << endl;
			cout << "checkin <room> <from> <to> <note> <guests> - Registration in <room> in the period <from> <to> with <guests>" << endl;
			cout << "availability <date> - Checks room availability on <date>" << endl;
			cout << "checkout <room> - Checks out guests from <room>" << endl;
			cout << "find <beds> <from> <to> - Finds available room with <beds> in the period <from> <to>" << endl;
			cout << "find! <beds> <from> <to> - Finds urgent search for a special guest with <beds> in the period" << endl;
			cout << "unavailable <room> <from> <to> <note> - Setting <room> as unavailable for period <from> <to>" << endl;
			break;
		case 6:
			// Exit
			cout << "Exiting the program..."<<endl;
			exited = 1;
			break;
		case 7:
			// Checkin
			if (out.is_open()) {
				numOfRoom = arguments[1].toInteger();
				date1String = arguments[2];
				date2String = arguments[3];
				numOfGuests = arguments[5].toInteger();
				note = arguments[4];

				Operation::initPeriodFromCommand(period, year1, day1, month1, date1, date1String, year2, day2, month2, date2, date2String);

				if (!(numOfGuests >= 1 && numOfGuests <= 5)) {
					cout << "The note has to be one word or that was an error with the number of guests." << endl;
					break;
				}

				hotel.checkin(numOfRoom, period, note, numOfGuests);
			}
			else {
				cout << "You have to open a file to enter this command!" << endl;
			}

			break;
		case 8:
			// Availability
			if (out.is_open()) {
				date1String = arguments[1];

				if (arguments.getSize() > 1) {
					Operation::initDateFromCommand(period, date1String, date1, year1, day1, month1);
					hotel.availability(period);
				}
				else {
					cout << "Missing arguments!" << endl;
				}
			}
			else {
				cout << "You have to open a file to enter this command!" << endl;
			}

			break;
		case 9:
			// Checkout
			if (out.is_open()) {
				numOfRoom = arguments[1].toInteger();
				hotel.checkout(numOfRoom);
			}
			else {
				cout << "You have to open a file to enter this command!" << endl;
			}

			break;
		case 10:
			// Report
			if (out.is_open()) {
				date1String = arguments[1];
				date2String = arguments[2];

				Operation::initPeriodFromCommand(period, year1, day1, month1, date1, date1String, year2, day2, month2, date2, date2String);
				hotel.report(period);
			}
			else {
				cout << "You have to open a file to enter this command!" << endl;
			}

			break;
		case 11:
			// Find
			if (out.is_open()) {
				beds = arguments[1].toInteger();
				date1String = arguments[2];
				date2String = arguments[3];

				Operation::initPeriodFromCommand(period, year1, day1, month1, date1, date1String, year2, day2, month2, date2, date2String);

				if (period.countDaysBetween() < 0)
					period.setInitializedCorrectly(0);

				if (period.wasInitializedCorrectly())
					hotel.find(beds, period);
				else {
					cout << "Wrong date input!" << endl;
				}
			}
			else {
				cout << "You have to open a file to enter this command!" << endl;
			}
			
			break;
		case 12:
			// Find important
			if (out.is_open()) {
				beds = arguments[1].toInteger();
				date1String = arguments[2];
				date2String = arguments[3];

				Operation::initPeriodFromCommand(period, year1, day1, month1, date1, date1String, year2, day2, month2, date2, date2String);

				if (period.countDaysBetween() < 0)
					period.setInitializedCorrectly(0);

				if (period.wasInitializedCorrectly())
					hotel.find_important(beds, period);
				else {
					cout << "Wrong date input!" << endl;
				}
			}
			else {
				cout << "You have to open a file to enter this command!" << endl;
			}

			break;
		case 13:
			// Unavailable
			if (out.is_open()) {
				numOfRoom = arguments[1].toInteger();
				date1String = arguments[2];
				date2String = arguments[3];
				note = arguments[4];

				Operation::initPeriodFromCommand(period, year1, day1, month1, date1, date1String, year2, day2, month2, date2, date2String);

				hotel.unavailable(numOfRoom, period, note);
			}
			else {
				cout << "You have to open a file to enter this command!" << endl;
			}

			break;
		default:
			cout << "Invalid command entered!" << endl;
			break;
		}
	} while (!exited);
}


String ConsoleEngine::subString(String text, int startPosition, int endPosition) {
	String result;
	for (size_t i = 0; i < endPosition - startPosition; i++) {
		result = result + text[startPosition + i];
	}

	result[endPosition - startPosition] = 0;
	return result;
}

int ConsoleEngine::countLetters(String text, char letter)
{
	int counter = 0;
	int length = text.length();
	for (size_t i = 0; i < length; i++) {
		if (text[i] == letter)
			counter++;
	}

	return counter;
}

int ConsoleEngine::indexOf(String text, char letter)
{
	int length = text.length();
	for (size_t i = 0; i < length; i++) {
		if (text[i] == letter) {
			return i;
		}
	}

	return -1;
}

Vector<String> ConsoleEngine::split(String text)
{
	Vector<String> result;
	int spaces = countLetters(text, ' ');

	while (spaces) {
		result.push_back(subString(text, 0, indexOf(text, ' ')));
		text = subString(text, indexOf(text, ' ') + 1, text.length() + 1);
		spaces--;
	}

	result.push_back(text);
	return result;
}

int ConsoleEngine::toInt(String txt)
{
	int sum = 0;
	return sum;
}

int ConsoleEngine::checkOperation(String cmd) {
	Vector<String> cmdParts = split(cmd);

	for (size_t i = 0; i < 13; i++) {
		if (cmdParts[0] == commands_arr[i]) {
			return i + 1;
		}
			
	}

	return -1;
}
