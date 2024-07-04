#include "date.hpp"
#include <stdexcept>
#include <ctime>
#include <format>
#include <iostream>
#include <string>
#define WRONG_DAY "wrong day value (should be 1-31 differs for different months)"
#define WRONG_MONTH "wrong month value (should be 1-12)"
#define WRONG_YEAR "wrong year value (should be 1-9999)"

std::string date::to_string()
{
	std::string day_string 
	{ 
		(this->day >= 10) 
		? 
		std::to_string(this->day) 
		: 
		std::string { "0" } + std::to_string(this->day) 
	};

	std::string month_string
	{
		(this->month >= 10)
		?
		std::to_string(this->month)
		:
		std::string { "0" } + std::to_string(this->month)
	};

	std::string year_string
	{
		(this->year >= 10)
		?
		(
			this->year >= 100
			?
			(
				this->year >= 1000
				?
					std::to_string(this->year) 
				:
				std::string { "0" } + std::to_string(this->year)
			)
			:
			std::string { "00" } + std::to_string(this->year)
		)
		:
		std::string { "000" } + std::to_string(this->year)
	};

	return std::format("{}/{}/{}", day_string, month_string, year_string);
}

void date::set_day(int day)
{
	int maxDay { dateconstants::daysInMonths.find(this->month)->second };
	int minDay { 1 };

	if (this->month == 2 && (this->year % 100 == 0 ? this->year % 400 == 0 : this->year % 4 == 0)) 
	{
		maxDay = 29;
	}

	if (day < minDay || day > maxDay) {
		throw std::invalid_argument(WRONG_DAY);
	}

	this->day = day;
}

void date::set_month(int month)
{
	if (month < 1 || month > 12) {
		throw std::invalid_argument(WRONG_MONTH);
	}

	this->month = month;
}

void date::set_year(int year) 
{
	// Проверяем правильность года
	if (year < 1 || year > 9999) {
		throw std::invalid_argument(WRONG_YEAR);
	}

	this->year = year;
}

int date::get_day() {
	return this->day;
}

int date::get_month() {
	return this->month;
}

int date::get_year() {
	return this->year;
}

int date::get_max_day() {
	return dateconstants::daysInMonths.find(this->month)->second;
}