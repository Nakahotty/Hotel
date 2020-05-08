#pragma once
#include <iostream>
#include <fstream>
#include <ostream>
#include "Vector.h"
#include "String.h"
#include "Date.h"
#include "Period.h"
#include <cassert>

class Operation {
private:
	static void dateError() {
		cout << "Wrong date formation!" << endl;
	}
public:

	// Enter commands
	static void enterComand(String& cmd);
	static void enterNumOfRoom(int& numOfRoom);
	static void enterNote(String& note);
	static void enterNumOfGuets(int& enterNumOfGuets);
	static void enterBeds(int& beds);
	static void enterPeriod(Period& period, String& periodString, Date& date, int& year, int& day, int& month);

	// Modifying values
	static void clearStats(int& numOfRoom, Period& period, String& periodString, String& note, int& numOfGuests,
		int& year1, int& day1, int& month1, Date& date1, String& dateString1,
		int& year2, int& day2, int& month2, Date& date2, String& dateString2);

	static void initPeriod(Period& period,
		int& year1, int& day1, int& month1, Date& date1, String& dateString1,
		int& year2, int& day2, int& month2, Date& date2, String& dateString2);

	static void storeDates(int& numOfRoom, Period& period);

	// Validations 
	static void splitByTwo(const String& cmd, String& first, String& second);
	static void dateValidation(String& date, int& date_year, int& date_day, int& date_month);
	static bool isNumOfBedsValid(int& beds);
	static bool isNumOfRoomValid(int& numOfRoom);
	static bool isNumOFGuestsValid(int& numOfGuests);
};