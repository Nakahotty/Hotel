#pragma once
#include <iostream>
#include <cstring>
#include <fstream>

class String
{
public:
    char* str;

    String();
    String(const char* s);
    String(char c);
    String(const String& other);
    void init(const char* s);
    void print();
    const char* getName() const;
    String operator+ (char c);
    String operator+ (String other);
    bool operator== (String other);
    bool operator< (String other);
    size_t length() const;
    char operator[] (size_t i) const;
    char& operator[] (size_t i);
    String operator= (char c);

    // ADDED METHODS
    bool operator!= (String& other);
    bool contains(String& other);
    void toLower();
    int toInteger();
    char* c_str() {
        return this->str;
    }
};

std::ostream& operator<< (std::ostream& out, String s);
std::istream& operator>> (std::istream& in, String& s);