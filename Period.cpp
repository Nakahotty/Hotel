#include "Period.h"

Period::Period() {
	from = Date();
	to = Date();
	initializedCorrectly = 1;

	fromDateYear = from.getYear();
	toDateYear = to.getYear();

};

Period::Period(Date date) {
	from = date;
	to = date;

	fromDateYear = from.getYear();
	toDateYear = to.getYear();


	initDates();
}

Period::Period(Date _from, Date _to) {
	from = _from;
	to = _to;

	fromDateYear = from.getYear();
	toDateYear = to.getYear();

	initDates();
}

Date& Period::getDate() {
	return from;
}

void Period::addDefaultDate() {
	datesInPeriod.push_back(Date());
}

bool Period::checkAvailability() {
	if (from.getYear() != to.getYear() ||
		from.getMonth() < to.getMonth() - 1) {
		cout << "Wrong input!" << endl;
	}

	return true;
}

const Vector<Date>& Period::getDatesInPeriod() {
	return datesInPeriod;
}

size_t Period::getFromDateYear() const {
	return from.getYear();
}

size_t Period::getToDateYear() const {
	return to.getYear();
}

void Period::setInitializedCorrectly(bool correct) {
	initializedCorrectly = correct;
}

bool Period::wasInitializedCorrectly() const {
	return initializedCorrectly;
}

size_t Period::countDaysBetween() {
	const size_t monthDays[12] = { 31, 28, 31, 30, 31, 30,
								31, 31, 30, 31, 30, 31 };

	// Count number of dates before date1
	size_t countForFirstDate = from.getYear() * 365 + from.getDay();

	// Add days for months in given date 
	for (size_t i = 0; i < from.getMonth() - 1; i++)
		countForFirstDate += monthDays[i];

	// Count number of dates before date2
	size_t countForSecondDate = to.getYear() * 365 + to.getDay();

	// Add days for months in given date 
	for (size_t i = 0; i < to.getMonth() - 1; i++)
		countForSecondDate += monthDays[i];

	// Difference between the two is the num of days
	return countForSecondDate - countForFirstDate;
}

Period& Period::operator=(const Period& other) {
	if (this != &other) {
		datesInPeriod = other.datesInPeriod;
		from = other.from;
		to = other.to;
	}

	return *this;
}

bool Period::operator ==(const Period& other) {
	return from.getYear() == to.getYear() &&
		from.getDay() == to.getDay() &&
		from.getMonth() == to.getMonth();
}

bool Period::operator !=(const Period& other) {
	return !(*this == other);
}

ofstream& Period::savePeriod(ofstream& out) {

	from.saveDate(out);
	to.saveDate(out);

	size_t size = datesInPeriod.getSize();
	for (size_t i = 0; i < size; i++) {
		datesInPeriod[i].saveDate(out);
	}

	return out;
}

ifstream& Period::loadPeriod(ifstream& in) {

	from.loadDate(in);
	to.loadDate(in);

	size_t size = datesInPeriod.getSize();

	for (size_t i = 0; i < size; i++) {
		datesInPeriod[i].loadDate(in);
	}

	return in;
}