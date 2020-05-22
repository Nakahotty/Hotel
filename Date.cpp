#pragma once
#include "Date.h"

Date::Date() {
	this->year = 1970;
	this->day = 1;
	this->month = 1;
}

Date::Date(size_t year, size_t day, size_t month) {
	this->year = year;
	this->day = day;
	this->month = month;
}

Date::Date(const Date& other) {
	this->day = other.day;
	this->month = other.month;
	this->year = other.year;
}

Date& Date::operator=(const Date& other) {
	if (this != &other) {
		this->year = other.year;
		this->day = other.day;
		this->month = other.month;
	}

	return *this;
}

bool Date::operator==(const Date& other) {
	return (this->year == other.year &&
		this->month == other.month &&
		this->day == other.day);
}

size_t Date::getYear() const {
	return this->year;
}

size_t Date::getDay() const {
	return this->day;
}

size_t Date::getMonth() const {
	return this->month;
}

void Date::print() {
	cout << this->year << "-" << this->day << "-" << this->month << endl;
}

void Date::printHelper() const {
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

size_t Date::length() const {
	return this->dateLength;
}

// File input/output
ostream& Date::saveDate(ostream& out) const {
	out << this->year << "-" << this->day << "-" << this->month << endl;
	return out;
}

ifstream& Date::loadDate(ifstream& in) {
	in >> this->year;
	in.seekg(1, ios::cur);
	in >> this->day;
	in.seekg(1, ios::cur);
	in >> this->month;


	return in;
}