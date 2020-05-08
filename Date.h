#pragma once
#include <iostream>
#include "String.h"

using namespace std; 

class Date {
private:
	int year, day, month;
	int dateLength = 10;
public:
	Date() {
		this->year = 1970;
		this->day = 1;
		this->month = 1;
	}

	Date(int year, int day, int month) {
		this->year = year;
		this->day = day;
		this->month = month;
	}

	Date(const Date& other) {
		this->day = other.day;
		this->month = other.month;
		this->year = other.year;
	}

	Date& operator=(const Date& other) {
		if (this != &other) {
			this->year = other.year;
			this->day = other.day;
			this->month = other.month;
		}

		return *this;
	}

	bool operator==(const Date& other) {
		return (this->year == other.year &&
				this->month == other.month &&
				this->day == other.day);	
	}

	int getYear() const {
		return this->year;
	}

	int getDay() const {
		return this->day;
	}

	int getMonth() const {
		return this->month;
	}

	void print() {
		cout << this->year << "-" << this->day << "-" << this->month << endl;
	}

	void printHelper() const {
		String dayWithZero = "";
		String monthWithZero = "";

		if (day >= 1 && day <= 9) {
			dayWithZero = "0";
		}

		if (month >= 1 && month <= 9) {
			monthWithZero = "0";
		}

		cout << dayWithZero << this->day << "-" << monthWithZero << this->month << " ";
	}

	int length() const {
		return this->dateLength;
	}
};