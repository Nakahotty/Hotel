#pragma once
#include "Date.h"

class Period {
private:
	Date from;
	Date to;
	Vector<Date> datesInPeriod;

	void printDates() const {
		cout << "You selected the dates " << endl;

		for (size_t i = 0; i < datesInPeriod.getSize(); i++) {
			datesInPeriod[i].printHelper();
		}

		cout << endl;
	}

	void initDates() {
		int countDays = countDaysBetween();

		for (size_t i = 0; i <= countDays; i++) {
			if (from.getYear() != to.getYear()) {
				cout << "You cannot define periods accross years!" << endl;
				break;
			}
			else if (from.getMonth() > to.getMonth()) {
				cout << "Wrong month input!" << endl;
			}
			else {
				if (countDays > 62) {
					cout << "You cannot reserve for more than 2 months ahead!" << endl;
					break;
				}

				int dayOfStartDate = from.getDay();
				int monthOfStartDate = from.getMonth();
				int helper;

				if (dayOfStartDate + i > 31) {
					monthOfStartDate++;
					helper = i - 31;


					if (dayOfStartDate + helper > 31) {
						monthOfStartDate++;
						dayOfStartDate -= 31;
					}

					datesInPeriod.push_back(Date(from.getYear(), dayOfStartDate + helper, monthOfStartDate));
				}
				else {
					datesInPeriod.push_back(Date(from.getYear(), dayOfStartDate + i, monthOfStartDate));
					
					if (from == to) {
						cout << "You reserved a room for 1 day!" << endl;
						break;
					}
				}
			}

		}
	}

public:
	Period() { 
		from = Date();
		to = Date();
	};

	Period(Date date) {
		from = date;
		to = date;
		
		initDates();
	}

	Period(Date _from, Date _to) {
		from = _from;
		to = _to;

		initDates();
		printDates();
	}

	Date& getDate() {
		return from;
	}
	
	void addDefaultDate() {
		datesInPeriod.push_back(Date());
	}

	bool checkAvailability() {
		if (from.getYear() != to.getYear() ||
			from.getMonth() < to.getMonth() - 1) {
			cout << "Wrong input!" << endl;
		}

		return true;
	}

	const Vector<Date>& getDatesInPeriod() {
		return datesInPeriod;
	}

	int countDaysBetween() {
		const int monthDays[12] = { 31, 28, 31, 30, 31, 30,
									31, 31, 30, 31, 30, 31 };

		// Count number of dates before date1
		int countForFirstDate = from.getYear() * 365 + from.getDay();

		// Add days for months in given date 
		for (size_t i = 0; i < from.getMonth() - 1; i++)
			countForFirstDate += monthDays[i];

		// Count number of dates before date2
		int countForSecondDate = to.getYear() * 365 + to.getDay();

		// Add days for months in given date 
		for (size_t i = 0; i < to.getMonth() - 1; i++)
			countForSecondDate += monthDays[i];

		// Difference between the two is the num of days
		return countForSecondDate - countForFirstDate;
	}

	Period& operator=(const Period& other) {
		if (this != &other) {
			datesInPeriod = other.datesInPeriod;
			from = other.from;
			to = other.to;
		}

		return *this;
	}

	bool operator ==(const Period& other) {
		return from.getYear() == to.getYear() &&
			from.getDay() == to.getDay() &&
			from.getMonth() == to.getMonth();
	}

	bool operator !=(const Period& other) {
		return !(*this == other);
	}
};