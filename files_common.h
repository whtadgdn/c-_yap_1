#pragma once
#include "student.h"
#include <iostream>
#include "date.hpp"
#include <string>
#include <fstream>
#include <filesystem>

bool createFile(std::string student_number) {
	student_number += ".student";
	student_number = "data/" + student_number;
	if (std::filesystem::exists(student_number))
		return true;
	while (!std::filesystem::exists(student_number)) {
		std::filesystem::path pathfs(student_number);
		std::ofstream ofs(pathfs);
		ofs.close();
	}
	return true;
}

bool exists(std::string student_number) {
	return (std::filesystem::exists(student_number + ".student"));
}