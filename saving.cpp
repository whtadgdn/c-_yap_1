#include "saving.h"
#include <iostream>
#include "date.hpp"
#include <string>
#include <fstream>
#include <filesystem>
#include "cereal/cereal.hpp"
#include <cereal/types/memory.hpp>
#include <cereal/types/concepts/pair_associative_container.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/array.hpp>
#include <cereal/archives/binary.hpp>

std::vector<student> parse_all_students() {
	std::vector<student> result;
	for (auto& entry : std::filesystem::directory_iterator("data")) {
		if (!entry.is_directory() && entry.path().extension() == ".student") {
			std::ifstream os(entry.path(), std::ios::binary);
			cereal::BinaryInputArchive f(os);
			student student;
			f(student);
			result.push_back(student);
		}
	}
	std::sort(result.begin(), result.end());
	return result;
}

bool save(student t) {
	std::string student_number = "data/" + t.record_book_number;
	std::ofstream output_stream(student_number + ".student", std::ios::binary);
	cereal::BinaryOutputArchive archive(output_stream);
	archive(t);
	return true;
}

bool deletes(student t) {
	std::string student_number = "data/" + t.record_book_number + ".student";
	std::filesystem::remove(student_number);
	return true;
}