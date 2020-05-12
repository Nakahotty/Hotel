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

	do {
		cin >> cmd;
		Vector<String> arguments = split(cmd);
		arguments.print();

		switch (checkOperation(cmd)) {
		case 1:
			// Open
			cout << "Opening file..." << endl;
			break;
		case 2:
			// Close
			cout << "Closing file..." << endl;
			break;
		case 3:
			// Save
			cout << "Saving file..." << endl;
			break;
		case 4:
			// Save as
			cout << "Saving file as..." << endl;
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
			cout << "Checking in guests..." << endl;
			numOfRoom = arguments[1].toInteger();
			date1String = arguments[2];
			date2String = arguments[3];
			note = arguments[4];
			numOfGuests = arguments[5].toInteger();
			
			Operation::initPeriodFromCommand(period, year1, day1, month1, date1, date1String, year2, day2, month2, date2, date2String);
			hotel.checkin(numOfRoom, period, note, numOfGuests);

			break;
		case 8:
			// Availability
			cout << "Getting available rooms..." << endl;

			date1String = arguments[1];

			Operation::initDateFromCommand(period, date1String, date1, year1, day1, month1);
			hotel.availability(period);
			break;
		case 9:
			// Checkout
			cout << "Checking out room..." << endl;

			numOfRoom = arguments[1].toInteger();
			hotel.checkout(numOfRoom);
			break;
		case 10:
			// Report
			cout << "Getting report..." << endl;

			date1String = arguments[1];
			date2String = arguments[2];

			Operation::initPeriodFromCommand(period, year1, day1, month1, date1, date1String, year2, day2, month2, date2, date2String);
			hotel.report(period);
			break;
		case 11:
			// Find
			cout << "Finding an appropriate room ..." << endl;

			beds = arguments[1].toInteger();
			date1String = arguments[2];
			date2String = arguments[3];

			Operation::initPeriodFromCommand(period, year1, day1, month1, date1, date1String, year2, day2, month2, date2, date2String);
			hotel.find(beds, period);
			break;
		case 12:
			// Find important
			cout << "Finding a room for an important person..." << endl;

			beds = arguments[1].toInteger();
			date1String = arguments[2];
			date2String = arguments[3];

			Operation::initPeriodFromCommand(period, year1, day1, month1, date1, date1String, year2, day2, month2, date2, date2String);
			hotel.find_important(beds, period);
			break;
		case 13:
			// Unavailable
			numOfRoom = arguments[1].toInteger();
			date1String = arguments[2];
			date2String = arguments[3];
			note = arguments[4];

			Operation::initPeriodFromCommand(period, year1, day1, month1, date1, date1String, year2, day2, month2, date2, date2String);
			hotel.unavailable(numOfRoom, period, note);
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
	for (size_t i = 0; i < text.length(); i++) {
		if (text[i] == letter)
			counter++;
	}

	return counter;
}

int ConsoleEngine::indexOf(String text, char letter)
{
	for (size_t i = 0; i < text.length(); i++) {
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
