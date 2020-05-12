	#include "Operation.h"

void Operation::splitByTwo(const String& cmd, String& first, String& second) {
	int spaceIndex = 0;

	if (cmd[0] == '\0') {
		cout << "Missing input!" << endl;
		return;
	}

	// If there is no second word
	bool foundSecond = 0;
	for (size_t i = 0; i < cmd.length(); i++) {
		if (cmd[i] == ' ') {
			foundSecond = 1;
		}
	}

	if (foundSecond) {
		// Skipping spaces
		int counterFirstWord = 0;
		for (size_t i = 0; cmd[i] == ' '; i++) {
			counterFirstWord++;
		}

		int copyCounterFirstWord = counterFirstWord; // For later 

		// Storing the first command
		

		for (size_t i = counterFirstWord; cmd[i] != ' '; i++) {
			first = first + cmd[i];
			counterFirstWord++;

			// If there is no second argument
			if (cmd[counterFirstWord] == '\0') {
				cout << "Missing arguments!" << endl;
				return;
			}
		}

		// Skipping spaces
		int counterSecondWord = 0;
		for (size_t i = counterFirstWord; cmd[i] == ' '; i++) {
			counterSecondWord++;
		}

		// Storing the second command
		for (size_t i = copyCounterFirstWord + first.length() + counterSecondWord; i <= cmd.length(); i++) {
			second = second + cmd[i];
		}

		if (cmd[0] != '\0') {
			cout << "User command: " << first << endl;
			cout << "File location: " << second << endl;
		}
	}
	else {
		cout << "Missing arguments!" << endl;
	}
	
}

Operation::Operation(Hotel& hotel, int& numOfRoom, int& numOfGuests, String& note, Period& period, String& periodString, 
	                 int& year1, int& day1, int& month1, int& year2, int& day2, int& month2, String& date1String, 
	                 String& date2String, Date& date1, Date& date2, int& beds) {
	
}

void Operation::enterComand(String& cmd) {
	cout << "$ "; cin >> cmd;
}

void Operation::dateValidation(String& date, int& date_year, int& date_day, int& date_month) {
	int countDashes = 0;

	if (date[0] == '\0') {
		cout << "Wrong input!" << endl;
		return;
	}

	for (size_t i = 0; i < date.length(); i++) {
		if (date[i] == '-')
			countDashes++;
	}

	if (countDashes != 2 || date.length() != 10) {
		dateError();
		return;
	}

	String yearString, dayString, monthString;
	int firstDash = 0, secondDash = 0;

	if (date[4] == '-') {
		for (size_t i = 0; i < 4; i++) {
			yearString = yearString + date[i];
			firstDash++;
		}

		dayString = 0;
		if (date[7] == '-') {
			for (size_t i = 5; i < 7; i++) {
				dayString = dayString + date[i];
			}

			for (size_t i = 8; i < 10; i++) {
				monthString = monthString + date[i];
			}
		}
		else {
			dateError();
		}
	}
	else {
		dateError();
	}

	date_year = yearString.toInteger();
	date_day = dayString.toInteger();
	date_month = monthString.toInteger();


	if (date_year < 2019 ||
		date_day < 1 ||
		date_day > 31 ||
		date_month < 1 ||
		date_month > 12) {
		cout << "Wrong input on either year/day/month." << endl; return;
	}
}

bool Operation::isNumOfBedsValid(int& beds)
{
	return beds >= 1 && beds <= 4;
}

bool Operation::isNumOfRoomValid(int& numOfRoom)
{
	return numOfRoom >= 1 && numOfRoom <= 100;
}

bool Operation::isNumOFGuestsValid(int& numOfGuests)
{
	return numOfGuests >= 1 && numOfGuests <= 4;
}

void Operation::initPeriodFromCommand(Period& period, int& year1, int& day1, int& month1, Date& date1, String& dateString1, int& year2, int& day2, int& month2, Date& date2, String& dateString2)
{
	Operation::dateValidation(dateString1, year1, day1, month1);
	date1 = Date(year1, day1, month1);

	Operation::dateValidation(dateString2, year2, day2, month2);
	date2 = Date(year2, day2, month2);

	period = Period(date1, date2);
}

void Operation::initDateFromCommand(Period& period, String& periodString, Date& date, int& year, int& day, int& month)
{
	Operation::dateValidation(periodString, year, day, month);

	date = Date(year, day, month);
	period = Period(date);
}

void Operation::enterNumOfRoom(int& numOfRoom)
{
	cout << "Number of Room" << endl;
	cout << "$ "; cin >> numOfRoom; cin.ignore();

	if (!isNumOfRoomValid(numOfRoom)) {
		cout << "Not allowed value of room!" << endl;
		assert(false);
	}
		
}

void Operation::enterDate(Period& period, String& periodString, Date& date, int& year, int& day, int& month) {
	cout << "Date " << endl;
	cout << "$ ";

	cin >> periodString;

	Operation::dateValidation(periodString, year, day, month);

	date = Date(year, day, month);
	period = Period(date);
}

void Operation::clearStats(int& numOfRoom, Period& period, String& periodString, String& note, int& numOfGuests, 
						   int& year1, int& day1, int& month1, Date& date1, String& dateString1,
	                       int& year2, int& day2, int& month2, Date& date2, String& dateString2) {
	numOfRoom = 0;
	periodString = String();
	note = String();
	numOfGuests = 0;
	year1 = year2 = 0;
	day1 = day2 = 0;
	month1 = month2 = 0;
	date1 = date2 = Date();
	dateString1 = dateString2 = String();
}

void Operation::initPeriod(Period& period, int& year1, int& day1, int& month1, Date& date1, String& dateString1, int& year2, int& day2, int& month2, Date& date2, String& dateString2)
{
	Operation::enterComand(dateString1);
	Operation::dateValidation(dateString1, year1, day1, month1);
	Date date1_new(year1, day1, month1);

	Operation::enterComand(dateString2);
	Operation::dateValidation(dateString2, year2, day2, month2);
	Date date2_new(year2, day2, month2);

	period = Period(date1_new, date2_new);
}

void Operation::storeDates(int& numOfRoom, Period& period)
{
	
}

void Operation::enterNote(String& note)
{
	cout << "Note" << endl;
	cout << "$ "; cin >> note; 
}

void Operation::enterNumOfGuets(int& numOfGuests)
{
	cout << "Number of guests" << endl;
	cout << "$ "; cin >> numOfGuests; cin.ignore();

	if (!isNumOFGuestsValid(numOfGuests)) {
		cout << "Not allowed value for guests!" << endl;
		assert(false);
	}
}

void Operation::enterBeds(int& beds)
{
	cout << "Number of beds" << endl;
	cout << "$ "; cin >> beds; cin.ignore();

	if (!isNumOfBedsValid(beds)) {
		cout << "Not allowed value for beds!" << endl;
		assert(false);
	}
}


