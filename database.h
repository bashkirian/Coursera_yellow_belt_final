#pragma once
#include "date.h"
#include <vector>
#include <map>
#include <list>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
using namespace std;

class Database
{
	map<const Date, vector<string>> storage;
	map<const Date, set<string>> set_storage;
public:

	void Add(const Date& date, const string& event)
	{
		if (!event.empty() && (set_storage[date].count(event) == 0))
		{
			storage[date].push_back(event);
			set_storage[date].insert(event);
		}
	};

	template <typename Func>
	int RemoveIf(Func f) {
		int count = 0;
		map<const Date, vector<string>> storage_c = storage;
		for (auto d : storage_c) {
			vector<string> events = d.second;
			auto it1 = stable_partition(events.begin(), // делим events на часть которая не удовл условию и
				events.end(), [f, &d](const string& s) // которая удовлетворяет
				{return !f(d.first, s); });

			count += events.end() - it1; // число событий которые удовлетворяют

			events.erase(it1, end(events)); // удаляем которые удовлетворяют
			if (events.size() == 0) { // если удалили все события произошедшие в какую-то дату
				storage.erase(d.first);
				set_storage.erase(d.first);
			}
			else { // иначе присваиваем измененные события
				storage[d.first] = events;
				set_storage[d.first] = set<string>(events.begin(), events.end());
			}
		}
		return count;
	}

	template <typename Func>
	vector<pair<Date, string>> FindIf(Func f) const {
		vector<pair<Date, string>> founded;
		for (auto d : storage) {
			vector<string> events = d.second;
			auto border = stable_partition(events.begin(),
				events.end(), [f, &d](const string& s)
				{return f(d.first, s); });
			if (border != events.begin())
			{
				vector<pair<Date, string>> foo(border - events.begin());
				for (int i = 0; i < border - events.begin(); ++i)
				{
					foo[i] = make_pair(d.first, events[i]);
				}
				founded.insert(founded.end(), foo.begin(), foo.end());
			}
		}
		return founded;
	}
	pair<Date, string> Last(const Date & last_date) const;
	void Print(ostream& cout) const;
};

ostream& operator<<(ostream& os, const pair<Date, vector<string>>& pair_);

ostream& operator<<(ostream& os, const pair<Date, string>& pair_);