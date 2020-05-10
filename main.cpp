#include "Hotel.h"
#include "ConsoleEngine.h"
#include <time.h>

int main() {
	srand(time(NULL));

	Hotel nasko;
	int numOfRoom; int numOfGuests; String note;
	Period period;
	String periodString;
	int year1, day1, month1, year2, day2, month2;
	String date1String, date2String;
	Date date1, date2;
	int beds;

	ConsoleEngine milen;
	milen.run();
	


	/*       COMMAND & DATE TEST
	String cmd;
	Operation::enterComand(cmd);
	String userCmd, fileLocation;
	Operation::splitByTwo(cmd, userCmd, fileLocation);

	int date_year, date_day, date_month;
	String date;
	Operation::enterComand(date);
	Operation::dateValidation(date, date_year, date_day, date_month);
	*/


	//       REPORT TEST
	/*
	Operation::initPeriod(period, year1, day1, month1, date1, date1String,
		year2, day2, month2, date2, date2String);

	nasko.report(period);

	Operation::clearStats(numOfRoom, period, periodString, note, numOfGuests,
		year1, day1, month1, date1, date1String,
		year2, day2, month2, date2, date2String);
	*/


	//        CHECKIN TEST
	cout << "Checking in..." << endl;
	Operation::enterNumOfRoom(numOfRoom);
	Operation::initPeriod(period, year1, day1, month1, date1, date1String,
		year2, day2, month2, date2, date2String);
	Operation::enterNote(note);
	Operation::enterNumOfGuets(numOfGuests);

	nasko.checkin(numOfRoom, period, note, numOfGuests);

	// Operation::storeDates(numOfRoom, period);
	Operation::clearStats(numOfRoom, period, periodString, note, numOfGuests,
						  year1, day1, month1, date1, date1String,
						  year2, day2, month2, date2, date2String);

	//        CHECKIN TEST
	cout << "Checking in..." << endl;
	Operation::enterNumOfRoom(numOfRoom);
	Operation::initPeriod(period, year1, day1, month1, date1, date1String,
		year2, day2, month2, date2, date2String);
	Operation::enterNote(note);
	Operation::enterNumOfGuets(numOfGuests);

	nasko.checkin(numOfRoom, period, note, numOfGuests);

	// Operation::storeDates(numOfRoom, period);
	Operation::clearStats(numOfRoom, period, periodString, note, numOfGuests,
		year1, day1, month1, date1, date1String,
		year2, day2, month2, date2, date2String);


	//        AVAILABILITY TEST
	cout << "Checking availability..." << endl;
	Operation::enterPeriod(period, periodString, date1, year1, day1, month1);
	nasko.availability(period);

	Operation::clearStats(numOfRoom, period, periodString, note, numOfGuests,
		year1, day1, month1, date1, date1String,
		year2, day2, month2, date2, date2String);


	/*       FIND AND FIND IMPORTANT TEST
	Operation::initPeriod(period, year1, day1, month1, date1, date1String,
		year2, day2, month2, date2, date2String);
	Operation::enterBeds(beds);
	
	nasko.find_important(beds, period);
	*/


	/*      UNAVAILABLE TEST
	Operation::enterNumOfRoom(numOfRoom);
	Operation::enterPeriod(period, periodString);
	Operation::enterNote(note);
	nasko.unavailable(numOfRoom, period, note);
	*/


	// initperiod();
	// report(period);
	// clearStats();



















	/*

	if (userCmd == "open") {
		// function ...
		// ostream& os (fileLocation);
	}

	while (true) {

		if (userCmd == "open") {
			cout << "Opening file..." << endl;
			ifstream inputStream("hotel.txt");
			break;
		}
		else if (userCmd == "close") {
			cout << "Closing file... " << endl;
		}
		else if (userCmd == "save") {
			cout << "Saving file..." << endl;
			ofstream outputStream("hotel.txt");
			break;
		}
		else if (userCmd == "save_as") {
			cout << "Saving file as: " << " " << endl;
		}
		else if (userCmd == "help") {
			
		}
		else if (userCmd == "exit") {
			cout << "Exiting program..." << endl;
			break;
		}
		else {
			cmd = "";
			cin >> cmd;
		}

	}
	*/
}