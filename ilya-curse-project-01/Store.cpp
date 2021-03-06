#include "Store.h"

std::string Store::toString() {
	std::string result = std::to_string(getId()) + ";" + name + "\n";
	return result;
}

void Store::fromString(std::string input) {
	std::string idStr = input.substr(0, input.find(";"));
	std::string nameStr = input.substr(input.find(";") + 1, input.length());

	try {
		int id = std::stoi(idStr);

		if (id >= 0) {
			name = nameStr;
			setId(id);
		}
		else {
			throw std::runtime_error("Invalid region id");
		}
	}
	catch (std::exception e) {
		std::cout << "Region Id is incorrect, or wrong format.";
		throw e;
	}
}

std::string Store::getName() {
	return name;
}

void Store::setName(std::string& name) {
	this->name = name;
}
