#include "Section.h"

std::string Section::toString() {
	std::string result = std::to_string(getId()) + ";" + name + "\n";
	return result;
}

void Section::fromString(std::string input) {
	std::string idStr = input.substr(0, input.find(";"));
	std::string nameStr = input.substr(input.find(";") + 1, input.length());

	try {
		int id = std::stoi(idStr);

		if (id >= 0) {
			name = nameStr;
			setId(id);
		}
		else {
			throw std::runtime_error("Invalid section id");
		}
	}
	catch (std::exception e) {
		std::cout << "Section Id is incorrect, or wrong format.";
		throw e;
	}
}

std::string Section::getName() {
	return name;
}

void Section::setName(std::string& name) {
	this->name = name;
}
