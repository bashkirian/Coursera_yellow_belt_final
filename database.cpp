#include "database.h"
#include "date.h"
#include <stdexcept>
#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

ostream& operator<<(ostream& os, const pair<Date, string>& pair_)
{
    os << pair_.first << " " << pair_.second;

    return os;
}

ostream& operator<<(ostream& os, const pair<Date, vector<string>>& pair_)
{
    for (const auto& item : pair_.second)
    {
        os << pair_.first << " " << item << endl;
    }
    return os;
}

void Database::Print(ostream& cout) const
{
    for (const auto& dates : storage)
    {
        for (const string& chores : dates.second)
        {
            cout << dates.first << " ";
            cout << chores << endl;
        }
    }
};

pair<Date, string> Database::Last(const Date& last_date) const
{
    if (storage.begin() == storage.end()) throw invalid_argument("empty database");
    auto date_lower = storage.upper_bound(last_date);
    if (date_lower == storage.begin()) throw invalid_argument("no less dates");
    --date_lower;
    return make_pair(date_lower->first, date_lower->second.back());
}
