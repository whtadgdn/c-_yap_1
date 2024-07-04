#pragma once
#include <array>
#include "date.hpp"
#include <numeric>
#include <algorithm>

struct subject {
	std::string name;
	int mark = 0;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(
			name,
			mark
		);
	}
};

struct student {
	std::string first_name;
	std::string last_name;
	std::string middle_name;
	date birth_date;
	date admission_date;
	std::string faculty;
	std::string group;
	std::string record_book_number;
	bool is_male;
	std::array<std::array<subject, 10>, 9> terms;

	student() = default;

	student(
		std::string first_name,
		std::string last_name,
		std::string middle_name,
		date birth_date,
		date admission_date,
		std::string faculty,
		std::string group,
		std::string record_book_number,
		bool is_male
	) {
		this->first_name = first_name;
		this->last_name = last_name;
		this->middle_name = middle_name;
		this->birth_date = birth_date;
		this->admission_date = admission_date;
		this->faculty = faculty;
		this->group = group;
		this->record_book_number = record_book_number;
		this->is_male = is_male;
	}

	bool operator < (const student& other) const
	{
		std::vector<int> my_marks;
		std::vector<int> other_marks;

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 10; j++) {
				int mark = this->terms[i][j].mark;
				int his_mark = other.terms[i][j].mark;

				if (mark != 0) my_marks.push_back(mark);
				if (his_mark != 0) other_marks.push_back(his_mark);
			}
		}

		float my_perc = std::reduce(my_marks.begin(), my_marks.end());
		float other_perc = std::reduce(other_marks.begin(), other_marks.end());

		return my_perc < other_perc;
	}

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(
			first_name,
			last_name,
			middle_name,
			birth_date,
			admission_date,
			faculty,
			group,
			record_book_number,
			is_male,
			terms
		);
	}
};