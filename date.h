#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;
class Date {
    int year;
    int month;
    int day;
public:
    Date(const int& new_year, const int& new_month, const int& new_day);
    Date() : year(0), month(0), day(0) {};
    int GetYear() const 
    {
        return year;
    };
    int GetMonth() const 
    {
        return month;
    };
    int GetDay() const
    {
        return day;
    };
    Date& operator=(const Date& other);
};

ostream& operator << (ostream& stream, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);

Date ParseDate(istream& input);