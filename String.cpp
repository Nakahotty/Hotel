#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h> 
#include "String.h"

String::String()
{
    init("");
}

String::String(const char* s)
{
    init(s);
}

String::String(char c)
{
    str = new char[2];
    str[0] = c;
    str[1] = 0;
}

String::String(const String& other)
{
    str = new char[other.length() + 1];
    strcpy_s(str, other.length() + 1, other.str);
}

void String::init(const char* s)
{
    str = new char[strlen(s) + 1];
    strcpy_s(str, strlen(s) + 1, s);
}

//s1.print();
void String::print()
{
    std::cout << str << std::endl;
}

const char* String::getName() const
{
    return this->str;
}

String String::operator+ (char c)
{

    String result;
    //this->str -----> a b c \0 ....  | + z
    result.str = new char[length() + 1 + 1];
    //X X X X X
    strcpy_s(result.str, length() + 2, str);
    //a b c \0 X
    result.str[this->length()] = c;
    //a b c z X
    result.str[this->length() + 1] = 0;
    //newBuffer ---->  a b c z \0

    return result;

}

String String::operator+ (String other)
{
    String result;
    result.str = new char[strlen(str) + strlen(other.str) + 1];

    strcpy_s(result.str, strlen(str) + strlen(other.str) + 1, str);
    strcat_s(result.str, strlen(str) + strlen(other.str) + 1, other.str);

    return result;
}
//if (s1 == s2)
bool String::operator== (String other)
{
    return strcmp(str, other.str) == 0;
}
bool String::operator< (String other)
{
    return strcmp(str, other.str) < 0;
}
size_t String::length() const
{
    return strlen(str);
}

char String::operator[] (size_t i) const {
    return str[i];
}

char& String::operator[] (size_t i)
{
    return str[i];
}

//result = '0' + x;
//result.operator=('0'+x)
String String::operator= (char c)
{
    str = new char[2];
    str[0] = c;
    str[1] = 0;
    return *this;
}

bool String::operator!= (String& other)
{
    return !(this->str == other.str);
}

bool String::contains(String& other)
{
    size_t length1 = this->length();
    size_t length2 = other.length();

    for (size_t i = 0; i < length1 - length2; i++)
    {
        size_t j;
        for (j = 0; j < length2; j++) // Counts matching chars
        {
            if (this->str[i + j] != other.str[j])
                break;
        }

        if (j == length2) // If the number of matching chars is equal to the substring length -> true
            return true;
    }

    return false;
}

void String::toLower()
{
    for (size_t i = 0; this->str[i] != '\0'; i++)
    {
        if (this->str[i] >= 'A' && this->str[i] <= 'Z')
        {
            this->str[i] -= 'A' - 'a';
        }
    }
}

int String::toInteger() {
    int number = 0;
    number = std::atoi(this->str);

    /*
    for (size_t i = 0; this->str[i] != '\0'; i++) {
        
        if (str[i] >= '0' && str[i] <= '9') {
            int x = (int)(str[i]);
            number += x - 48;
        }
    }*/

    return number;
}

std::ostream& operator<< (std::ostream& out, String s)
{
    out << s.str;
    return out;
}

std::istream& operator>> (std::istream& in, String& s)
{
    s = "";
    char c;
    do
    {
        c = in.get();
        if (c != '\n')
        {
            s = s + c;
        }
    } while (c != '\n');

    return in;
}