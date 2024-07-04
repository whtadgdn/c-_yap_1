#pragma once
#include <unordered_map>

namespace dateconstants {
	const std::unordered_map<int, int> daysInMonths {
		{1, 31},
		{2, 28},
		{3, 31},
		{4, 30},
		{5, 31},
		{6, 30},
		{7, 31},
		{8, 31},
		{9, 30},
		{10, 31},
		{11, 30},
		{12, 31},
	};
}

// Самописная дата
class date {
private:

	int day;
	int month;
	int year;

public:

	date(int day, int month, int year) {
		this->set_year(year);
		this->set_month(month);
		this->set_day(day);
	}

	date() {
		this->set_year(1);
		this->set_month(1);
		this->set_day(1);
	}

	std::string to_string();
	void set_day(int day);
	int get_max_day();
	void set_month(int month);
	void set_year(int year);

	int get_day();
	int get_month();
	int get_year();

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(day, month, year);
	}
};