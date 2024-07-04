#include <iostream>
#include <vector>
#include "student.h"
#include "conmanip.h"
#include "keys.h"
#include "saving.h"
#include <numeric>
#include <algorithm>

#define con(x) std::cout << x

#define resf con(settextcolor(console_text_colors::white))
#define resb con(setbgcolor(console_bg_colors::black))

using namespace conmanip;

constexpr int window_height = 35;
constexpr int window_width = 120;

int get_key();
int get_key(const std::initializer_list<int> allowed);

void view_terms(student& student);

void border(int, int, int, int);

void groups_borders() {
	border(1, 0, window_width/2, window_height);
	con(setbgcolor(console_bg_colors::magenta));

	con(setpos(2, 0));
	con("50 percent good marks");

	con(setpos(window_width / 2 + 1, 0));
	con("others");

	resb;
	resf;
}

void students_columns() {
	
	border(1,  0, 26, window_height); // fio
	border(0,  0, 27, window_height); // fio
	border(26, 0, 12, window_height); // birthday
	border(37, 0, 12, window_height); // admission date
	border(48, 0, 23, window_height); // faculy
	border(70, 0, 23, window_height); // group
	border(92, 0, 23, window_height); // number
									  // gender does not need border
	con(setbgcolor(console_bg_colors::magenta));

	// fio
	con(setpos(2, 0));
	con("fio");

	// birthday
	con(setpos(27, 0));
	con("birth date");

	// admission
	con(setpos(38, 0));
	con("admission");

	// faculty
	con(setpos(49, 0));
	con("faculty");

	// group
	con(setpos(71, 0));
	con("group");

	// number
	con(setpos(93, 0));
	con("number");

	// gender
	con(setpos(115, 0));
	con("sex");

	resb;
	resf;
}

void border(int _x, int _y, int width, int height) {
	con(setbgcolor(console_bg_colors::magenta));
	for (int x = _x; x < _x + width; x++) 
	{
		for (int y = _y; y < _y + height; y++)
		{
			if (x == _x || x == _x + width - 1 || y == _y || y == _y + height - 1) {
				con(setpos(x, y));
				con(" ");
			}
		}
	}
	resf;
	resb;
}

void fill(int _x, int _y, int width, int height, console_bg_colors color) {
	con(setbgcolor(color));
	for (int x = _x; x < _x + width; x++)
	{
		for (int y = _y; y < _y + height; y++)
		{
				con(setpos(x, y));
				con(" ");
		}
	}
	resf;
	resb;
}

std::string get_concat_name(std::string f, std::string l, std::string m, int max_len = 24) {
	std::string concat = l + " " + f + " " + m;
	if (concat.length() > max_len) {
		concat = concat.substr(0, max_len - 3);
		concat += "...";
	}
	return concat;
}

std::string get_concat(std::string f, int max_len = 21) {
	std::string concat = f;
	if (concat.length() > max_len) {
		concat = concat.substr(0, max_len - 3);
		concat += "...";
	}
	return concat;
}

std::string get_concat_reverse(std::string concat, int max_len = 32) {
	if (concat.length() > max_len + 3) {
		int offset_index = concat.length() - max_len - 3;
		std::string res("...");
		res += concat.substr(offset_index, concat.length() - offset_index);
		return res;
	}
	return concat;
}

date get_date_from_user(date min, date max, date old) {
	date input_date(1, 1, 2022);
	int cur_pos = 0;
	int cur_pos_max = 2;

	for (;;) {
		fill(20, 7, 60, 20, console_bg_colors::light_white);
		con(setpos(20, 7));
		con(settextcolor(console_text_colors::black));
		con(setbgcolor(console_bg_colors::light_white));

		con(setpos(40, 16));
		con(input_date.to_string());

		switch (cur_pos) {
		default: break;
		case 0:
			con(setpos(40, 15));
			con("[day]");
			break;
		case 1:
			con(setpos(40, 15));
			con("[month]");
			break;
		case 2:
			con(setpos(40, 15));
			con("[year]");
			break;
		}

		con(setpos(24, 26));
		con("[ESC] cancel");

		con(setpos(56, 26));
		con("[ENTER] enter");

		switch (get_key())
		{
		default:
			break;
		case LEFT:
			cur_pos--;
			if (cur_pos < 0) cur_pos = cur_pos_max;
			break;
		case RIGHT:
			cur_pos++;
			if (cur_pos > cur_pos_max) cur_pos = 0;
			break;
		case DOWN:
			switch (cur_pos) {
			case 0:
				if (input_date.get_day() - 1 < 1) input_date.set_day(input_date.get_max_day());
				else input_date.set_day(input_date.get_day() - 1);
				break;
			case 1:
				if (input_date.get_month() - 1 < 1) { 
					input_date.set_month(12); 
					if (input_date.get_day() > input_date.get_max_day()) 
						input_date.set_day(input_date.get_max_day()); 
				}
				else { 
					input_date.set_month(input_date.get_month() - 1); 
					if (input_date.get_day() > input_date.get_max_day())
						input_date.set_day(input_date.get_max_day());
				}
				break;
			case 2:

				if (input_date.get_year() - 1 < 1) {
					input_date.set_year(2022);
				}
				else {
					input_date.set_year(input_date.get_year() - 1);
					if (input_date.get_day() > input_date.get_max_day())
						input_date.set_day(input_date.get_max_day());
				}
				break;
			}
			break;
		case UP:
			switch (cur_pos) {
			case 0:
				if (input_date.get_day() + 1 > input_date.get_max_day()) input_date.set_day(1);
				else input_date.set_day(input_date.get_day() + 1);
				break;
			case 1:
				if (input_date.get_month() + 1 > 12) {
					input_date.set_month(1);
					if (input_date.get_day() > input_date.get_max_day())
						input_date.set_day(input_date.get_max_day());
				}
				else {
					input_date.set_month(input_date.get_month() + 1);
					if (input_date.get_day() > input_date.get_max_day())
						input_date.set_day(input_date.get_max_day());
				}
				break;
			case 2:

				if (input_date.get_year() + 1 > 3000) {
					input_date.set_year(1970);
				}
				else {
					input_date.set_year(input_date.get_year() + 1);
					if (input_date.get_day() > input_date.get_max_day())
						input_date.set_day(input_date.get_max_day());
				}
				break;
			}
			break;
		case ENTER:
			return input_date;
		case ESC:
			return old;
		}
	}
}

bool get_bool_from_user(std::string true_text, std::string false_text, bool old = false) {
	bool input = old;
	for (;;) {
		fill(20, 7, 60, 20, console_bg_colors::light_white);
		con(setpos(20, 7));
		con(settextcolor(console_text_colors::black));
		con(setbgcolor(console_bg_colors::light_white));

		con(setpos(40, 16));
		con((input ? true_text : false_text));

		con(setpos(24, 26));
		con("[ESC] cancel");

		con(setpos(56, 26));
		con("[ENTER] enter");

		switch (get_key())
		{
		default:
			break;
		case LEFT:
			// fall through!
		case RIGHT:
			input = !input;
			break;
		case ENTER:
			return input;
		case ESC:
			return old;
		}
	}
}

std::string get_value_from_user(std::string description, std::string old) {

	std::string input;

	for (;;) {
		fill(20, 7, 60, 20, console_bg_colors::light_white);
		con(setpos(20, 7));
		con(settextcolor(console_text_colors::black));
		con(setbgcolor(console_bg_colors::light_white));
		con("enter a value: " + description);

		con(setpos(24, 13));
		con(get_concat(old, 32));

		con(setpos(24, 14));
		con("|");

		con(setpos(24, 15));
		con("V");

		con(setpos(24, 16));
		con(get_concat_reverse(input));

		con(setpos(24, 26));
		con("[ESC] cancel");

		con(setpos(56, 26));
		con("[ENTER] enter");

		char input_key = get_key();
		if ((input_key >= A && input_key <= Z) || (input_key >= N0 && input_key <= N9) || (input_key >= PLUS && input_key <= SLASH) || input_key == SPACEBAR) {
			input += input_key;
		}

		if (input_key == BACKSPACE && input.length() > 0) input.pop_back();

		if (input_key == ENTER && input.length() > 0) {
			return input;
		}

		if (input_key == ESC) {
			return old;
		}

	}
}

void add_new_student() {
	student student("DEFAULT", "DEFAULT", "DEFAULT", date(), date(), "DEFAULT", "DEFAULT", "DEFAULT", true);
	int fields_changed = 0;
	int fields_check = 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 ;

	int cursor_pos = 0;
	int cursor_pos_max = 8;

	fill(0, 0, window_width, window_height, console_bg_colors::black);
	for (;;) {
		system("cls");
		border(0, 0, window_width, window_height);

		if (fields_changed != fields_check) {
			con(settextcolor(console_text_colors::red));
			con(setpos(2, 1));
			con("edit all fields!");
			resf;
		}
		con(setpos(2, 2));
		con(student.first_name);

		con(setpos(2, 4));
		con(student.last_name);

		con(setpos(2, 6));
		con(student.middle_name);

		con(setpos(2, 8));
		con("birth date - " + student.birth_date.to_string());

		con(setpos(2, 10));
		con("admission date - " + student.admission_date.to_string());

		con(setpos(2, 12));
		con("faculty - " + student.faculty);

		con(setpos(2, 14));
		con("group - " + student.group);

		con(setpos(2, 16));
		con("number - " + student.record_book_number);

		con(setpos(2, 18));
		con(std::string("gender - ") + (student.is_male ? "Male" : "Female"));

		con(setpos(1, 2 + (cursor_pos * 2)));
		con(settextcolor(console_text_colors::cyan));
		con(">");

		switch (get_key()) {
		case X:
			if (fields_changed == fields_check) {
				save(student);
				return;
			}
			break;
		case Z:
			return;
			break;
		case UP:
			cursor_pos--;
			if (cursor_pos < 0) cursor_pos = cursor_pos_max;
			break;
		case DOWN:
			cursor_pos++;
			if (cursor_pos > cursor_pos_max) cursor_pos = 0;
			break;
		case ENTER:
			switch (cursor_pos)
			{
			default:
				break;
			case 0:
				student.first_name = get_value_from_user("enter a student's name", student.first_name);
				fields_changed |= 1;
				break;
			case 1:
				student.last_name = get_value_from_user("enter a student's last name", student.last_name);
				fields_changed |= 2;
				break;
			case 2:
				student.middle_name = get_value_from_user("enter a student's middle name", student.middle_name);
				fields_changed |= 3;
				break;
			case 3:
				student.birth_date = get_date_from_user(date(1, 1, 1900), date(1, 1, 2030), student.birth_date);
				fields_changed |= 4;
				break;
			case 4:
				student.admission_date = get_date_from_user(date(1, 1, 1900), date(1, 1, 2030), student.admission_date);
				fields_changed |= 5;
				break;
			case 5:
				student.faculty = get_value_from_user("enter a student's faculty", student.faculty);
				fields_changed |= 6;
				break;
			case 6:
				student.group = get_value_from_user("enter a student's group", student.group);
				fields_changed |= 7;
				break;
			case 7:
				student.record_book_number = get_value_from_user("enter a student's number", student.record_book_number);
				fields_changed |= 8;
				break;
			case 8:
				student.is_male = get_bool_from_user("male", "female", student.is_male);
				break;
			}
			fill(0, 0, window_width, window_height, console_bg_colors::black);
			system("cls");
			break;
		}
	}

}

bool is_50_percent(student student) {
	std::vector<int> marks_not_empty;
	std::vector<int> marks_good;
	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 10; j++) {
			int mark = student.terms[i][j].mark;

			if (mark != 0) marks_not_empty.push_back(mark);
			if (mark >= 4) marks_good.push_back(mark);
		}

	}

	float percent_good = ((float)marks_good.size() / ((float)marks_not_empty.size()));

	return percent_good >= 0.5f;
}

void draw_groups(std::vector<student> students) {
	std::vector<student> first_half;
	std::vector<student> second_half;

	for (auto& student : students) {
		if (is_50_percent(student)) {
			first_half.push_back(student);
		}
		else {
			second_half.push_back(student);
		}
	}

	std::sort(first_half.begin(), first_half.end());
	std::sort(second_half.begin(), second_half.end());


	fill(0, 0, window_width, window_height, console_bg_colors::black);
	for (;;) {
		system("cls");
		border(0, 0, window_width, window_height);
		groups_borders();
		con(setbgcolor(console_bg_colors::magenta));
		con(setpos(8, window_height - 1));
		con("(X) to exit");
		resb;

		for (int i = 0; i < 33; i++) {
			con(setpos(2, i + 1));
			if (!(first_half.size() < i + 1)) {
				auto& stud = first_half[i];
				con(stud.last_name << " " << stud.first_name << " " << stud.middle_name << " | " << stud.record_book_number);
			}
			con(setpos(2 + window_width/2, i + 1));
			if (!(second_half.size() < i + 1)) {
				auto& stud = second_half[i];
				con(stud.last_name << " " << stud.first_name << " " << stud.middle_name << " | " << stud.record_book_number);
			}
		}


		switch (get_key())
		{
		default:
			break;
		case X:
			return;
		}
	}
}

void draw_single_student_view(student student) {
	int cursor_pos = 0;
	int cursor_pos_max = 8;

	fill(0, 0, window_width, window_height, console_bg_colors::black);
	for (;;) {
		system("cls");
		border(0, 0, window_width, window_height);

		con(setbgcolor(console_bg_colors::magenta));
		con(setpos(8, window_height - 1));
		con("(X) to save and exit     (Z) to exit     (M) to view marks");
		resb;

		con(setpos(2, 2));
		con(student.first_name);

		con(setpos(2, 4));
		con(student.last_name);

		con(setpos(2, 6));
		con(student.middle_name);

		con(setpos(2, 8));
		con("birth date - " + student.birth_date.to_string());

		con(setpos(2, 10));
		con("admission date - " + student.admission_date.to_string());

		con(setpos(2, 12));
		con("faculty - " + student.faculty);

		con(setpos(2, 14));
		con("group - " + student.group);

		con(setpos(2, 16));
		con("number - " + student.record_book_number);

		con(setpos(2, 18));
		con(std::string("gender - ") + (student.is_male ? "Male" : "Female"));

		con(setpos(1, 2 + (cursor_pos * 2)));
		con(settextcolor(console_text_colors::cyan));
		con(">");

		switch (get_key()) {
		case X:
			save(student);
			return;
			break;
		case Z:
			return;
			break;
		case UP:
			cursor_pos--;
			if (cursor_pos < 0) cursor_pos = cursor_pos_max;
			break;
		case DOWN:
			cursor_pos++;
			if (cursor_pos > cursor_pos_max) cursor_pos = 0;
			break;
		case M:
			view_terms(student);
			break;
		case ENTER:
			switch (cursor_pos)
			{
			default:
				break;
			case 0:
				student.first_name = get_value_from_user("enter a student's name", student.first_name);
				break;
			case 1:
				student.last_name = get_value_from_user("enter a student's last name", student.last_name);
				break;
			case 2:
				student.middle_name = get_value_from_user("enter a student's middle name", student.middle_name);
				break;
			case 3:
				student.birth_date = get_date_from_user(date(1, 1, 1900), date(1, 1, 2030), student.birth_date);
				break;
			case 4:
				student.admission_date = get_date_from_user(date(1, 1, 1900), date(1, 1, 2030), student.admission_date);
				break;
			case 5:
				student.faculty = get_value_from_user("enter a student's faculty", student.faculty);
				break;
			case 6:
				student.group = get_value_from_user("enter a student's group", student.group);
				break;
			case 7:
				student.record_book_number = get_value_from_user("enter a student's number", student.record_book_number);
				break;
			case 8:
				student.is_male = get_bool_from_user("male", "female", student.is_male);
				break;
			}
			fill(0, 0, window_width, window_height, console_bg_colors::black);
			system("cls");
			break;
		}
	}

}

void view_terms(student& student) {

	int term_cursor = 0;
	int term_cursor_max = 8;

	int subject_cursor = 0;
	int subject_cursor_max = 9;

	for (;;) {
		system("cls");
		border(0, 0, window_width, window_height);

		con(setbgcolor(console_bg_colors::magenta));
		con(setpos(8, window_height - 1));
		con("(X) to save and exit    (S) to edit subject name    (M) to edit mark");
		resb;

		for (int i = 0; i < 10; i++) {
			border(1, i * 2 + 1, window_width - 1, 3);
		}
		con(setbgcolor(console_bg_colors::magenta));
		for (int i = 0; i < 10; i++) {
			con(setpos(0, i * 2 + 2));
			con(i + 1);
		}

		con(setpos(2, 0));
		con("term: " << (term_cursor + 1));

		resb;

		for (int i = 0; i < 10; i++) {
			if (subject_cursor == i) {
				con(setbgcolor(console_bg_colors::cyan));
			}
			con(setpos(2, i * 2 + 2));
			if (student.terms[term_cursor][i].name == "" && student.terms[term_cursor][i].mark == 0)
				con("EMPTY [-]");
			else if (student.terms[term_cursor][i].name == "") {
				con("EMPTY [" << student.terms[term_cursor][i].mark << "]");
			}
			else if (student.terms[term_cursor][i].mark == 0) {
				con(student.terms[term_cursor][i].name << " [-]");
			}
			else {
				con(student.terms[term_cursor][i].name << " [" << student.terms[term_cursor][i].mark << "]");
			}
			resb;
			resf;
		}


		switch (get_key())
		{
		default:
			break;
		case X:
			return;
		case LEFT:
			term_cursor--;
			if (term_cursor < 0) term_cursor = term_cursor_max;
			break;
		case RIGHT:
			term_cursor++;
			if (term_cursor > term_cursor_max) term_cursor = 0;
			break;
		case UP:
			subject_cursor--;
			if (subject_cursor < 0) subject_cursor = subject_cursor_max;
			break;
		case DOWN:
			subject_cursor++;
			if (subject_cursor > subject_cursor_max) subject_cursor = 0;
			break;
		case M:
			for (;;) {
				std::string inputstr = get_value_from_user("enter a mark (2-5)", "");
				try {
					if (std::stoi(inputstr) >= 2 && std::stoi(inputstr) <= 5) {
						student.terms[term_cursor][subject_cursor].mark = std::stoi(inputstr);
						break;
					}
				}
				catch (std::exception ex) {}
			}
			fill(0, 0, window_width, window_height, console_bg_colors::black);
			break;
		case S:
			std::string inputstr = get_value_from_user("enter a subject name", student.terms[term_cursor][subject_cursor].name);
			student.terms[term_cursor][subject_cursor].name = inputstr;
			fill(0, 0, window_width, window_height, console_bg_colors::black);
			break;
		}
	}
}


void draw_students() {
	
	// todo get all students
	std::vector<student> students = parse_all_students();
	int cursor_position = 0;
	int page = 0;
	
	fill(0, 0, window_width, window_height, console_bg_colors::black);
	for (;;) {
		system("cls");
		border(0, 0, window_width, window_height);
		students_columns();
		int ypos = 1;
		int index = 0;
		int max_page = students.size() / 33;
		auto stud_range = std::vector<student>(students.begin() + page * 33,

			students.size() >= page * 33 + 33 ? // is able to grab another 33

			students.begin() + page * 33 + 33 : // grab 33

			students.end());
		con(settextcolor(console_text_colors::white));
		con(setbgcolor(console_bg_colors::magenta));
		// page
		con(setpos(1, window_height - 1));
		con("<" << page + 1 << "/" << max_page + 1 << ">");

		
		con(setpos(8, window_height - 1));
		con("(ENTER) to inspect    (N) to add    (D) to delete    (P) to view sorted");
		resf;
		resb;

		for (auto s : stud_range) {
			if (ypos < window_height - 1) {

				con(settextcolor(console_text_colors::white));
				con(setbgcolor(console_bg_colors::magenta));

				// numbers
				con(setpos(0, ypos));
				con(index + 33 * page + 1);


				if (cursor_position == index) con(setbgcolor(console_bg_colors::green));

				con(settextcolor(console_text_colors::red));
				con(setpos(2, ypos));
				con(get_concat_name(s.first_name, s.last_name, s.middle_name));

				con(setpos(27, ypos));
				con(s.birth_date.to_string());

				con(setpos(38, ypos));
				con(s.admission_date.to_string());

				con(setpos(49, ypos));
				con(get_concat(s.faculty));

				con(setpos(71, ypos));
				con(get_concat(s.group));

				con(setpos(93, ypos));
				con(get_concat(s.record_book_number));

				con(setpos(116, ypos));
				if (s.is_male) {
					con(settextcolor(console_text_colors::blue));
					con("M");
				}
				else {
					con(settextcolor(console_text_colors::light_magenta));
					con("F");
				}
				
				resb;
				ypos++;
				index++;
			}
		}
		con(setpos(0, 0));
		resf;
		resb;
		switch (get_key()) {
		case P:
			draw_groups(students);
			break;
		case ENTER:
			if (students.size() > 0)
			draw_single_student_view(students[cursor_position]);
			students = parse_all_students();
			break;
		case D:
			deletes(students[cursor_position]);
			students = parse_all_students();
			break;
		case N:
			add_new_student();
			students = parse_all_students();
			break;
		case UP:
			cursor_position--;
			if (cursor_position < 0) {
				cursor_position = 32;
				cursor_position + page * 33 > students.size() - 1 ? cursor_position = students.size() % 33 - 1 : 32;
			}
			break;
		case DOWN:
			cursor_position++;
			if (cursor_position > 32 || cursor_position + page * 33 > students.size() - 1) {
				cursor_position = 0;
			}
			break;
		case LEFT:
			page--;
			cursor_position = 0;
			if (page < 0) page = max_page;
			break;
		case RIGHT:
			page++;
			cursor_position = 0;
			if (page > max_page) page = 0;
			break;
		}
	}
	
}

int main()
{

	console_out_context out_context;

	console_out out(out_context);

	out.settitle("Journal");

	draw_students();
		
	
	return 0;
}

int get_key(const std::initializer_list<int> allowed) {
	begin:
	const auto res = get_key();
	for (auto it = allowed.begin(); it != allowed.end(); ++it) {
		if (*it == res) return true;
	}
	goto begin;
}

int get_key()
{
	while (true)
	{
		for (int i = 8; i <= 256; i++)
		{
			if (GetAsyncKeyState(i) & 0x7FFF)
			{
				return i;
			}
		}
	}
}