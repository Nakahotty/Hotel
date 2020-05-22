#pragma once
#include <iostream>
#include "String.h"
#include "Vector.h"

using namespace std;

class Date {
private:
	size_t year, day, month;
	size_t dateLength = 10;
public:
	Date();
	Date(size_t year, size_t day, size_t month);
	Date(const Date& other);
	Date& operator=(const Date& other);
	bool operator==(const Date& other);

	size_t getYear() const;
	size_t getDay() const;
	size_t getMonth() const;

	void print();
	void printHelper() const;
	size_t length() const;

	// File input/output
	ostream& saveDate(ostream& out) const;
	ifstream& loadDate(ifstream& in); 
};