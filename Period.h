#pragma once
#include "Date.h"

class Period {
private:
	Date from;
	Date to;
	Vector<Date> datesInPeriod;

	size_t fromDateYear, toDateYear;
	bool initializedCorrectly;

	void printDates() const {
		if (fromDateYear == toDateYear) {
			cout << "You selected the dates " << endl;

			for (size_t i = 0; i < datesInPeriod.getSize(); i++) {
				datesInPeriod[i].printHelper();
			}

			cout << endl;
		}
		else {
			cout << "Error while initializing dates!" << endl;
		}
	}

	void initDates() {
		if (fromDateYear == toDateYear) {

			size_t countDays = countDaysBetween();

			if (countDays >= 0) {
				for (size_t i = 0; i <= countDays; i++) {
					if (from.getYear() != to.getYear()) {
						cout << "You cannot define periods accross years!" << endl;
						break;
					}
					else {
						if (from.getMonth() > to.getMonth()) {
							cout << "Wrong month input!" << endl;
							break;
						}

						if (countDays > 62) {
							cout << "You cannot reserve for more than 2 months ahead!" << endl;
							break;
						}

						size_t dayOfStartDate = from.getDay();
						size_t monthOfStartDate = from.getMonth();
						size_t helper;

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
						}
					}

				}
			}
			else {
				initializedCorrectly = 0;
			}
		}
	}

public:
	Period();
	Period(Date date);
	Period(Date _from, Date _to);
	Period& operator=(const Period& other);

	Date& getDate();
	void addDefaultDate();
	bool checkAvailability();
	const Vector<Date>& getDatesInPeriod();
	size_t getFromDateYear() const;
	size_t getToDateYear() const;
	void setInitializedCorrectly(bool correct);
	bool wasInitializedCorrectly() const;
	size_t countDaysBetween();

	bool operator ==(const Period& other);
	bool operator !=(const Period& other);
	ofstream& savePeriod(ofstream& out);
	ifstream& loadPeriod(ifstream& in);
};