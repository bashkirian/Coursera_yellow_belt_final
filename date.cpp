#include "date.h"
#include <sstream>
#include <iomanip>
using namespace std;

Date::Date(const int& new_year, const int& new_month, const int& new_day) : year(new_year), month(new_month), day(new_day) {};

ostream& operator << (ostream& stream, const Date& date)
{
    stream << setfill('0') << setw(4) << to_string(date.GetYear());
    stream << "-";
    stream << setfill('0') << setw(2) << to_string(date.GetMonth());
    stream << "-";
    stream << setfill('0') << setw(2) << to_string(date.GetDay());
    return stream;
};

bool operator<(const Date& lhs, const Date& rhs)
{
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
        vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}
bool operator<=(const Date& lhs, const Date& rhs)
{
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <=
        vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}
bool operator>=(const Date& lhs, const Date& rhs)
{
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >=
        vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}
Date& Date::operator=(const Date& other)
{
    this->year = other.GetYear();
	this->month = other.GetMonth();
	this->day = other.GetDay();

	return *this;
}
bool operator>(const Date& lhs, const Date& rhs)
{
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >
        vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}
bool operator!=(const Date& lhs, const Date& rhs)
{
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} !=
        vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}
bool operator==(const Date& lhs, const Date& rhs)
{
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} ==
        vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}
Date ParseDate(istream& input)
{
    int new_year, new_month, new_day;
    bool flag = true;
    flag = flag && (input >> new_year);
    flag = flag && (input.peek() == '-');
    input.ignore(1);
    flag = flag && (input >> new_month);
    flag = flag && (input.peek() == '-');
    input.ignore(1);
    flag = flag && (input >> new_day);
    if (!flag)
    {
        throw invalid_argument("Wrong date format: ");
    }
    if (new_month < 1 || new_month > 12)
    {
        throw out_of_range("Month value is invalid: " + to_string(new_month));
    }
    else if (new_day < 1 || new_day > 31)
    {
        throw runtime_error("Day value is invalid: " + to_string(new_day));
    }
    return Date(new_year, new_month, new_day);
}