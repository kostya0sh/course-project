#include "SectionItem.h"

std::string SectionItem::toString() {
	std::string result = std::to_string(getId()) + ";" + name + ";" + SectionItem::typeName(type) + "\n";
	return result;
}

void SectionItem::fromString(std::string input) {
	std::string idStr = input.substr(0, input.find(";"));
	std::string fieldsStr = input.substr(input.find(";") + 1, input.length());

	std::string nameStr = fieldsStr.substr(0, fieldsStr.find(";"));
	std::string typeStr = fieldsStr.substr(fieldsStr.find(";") + 1, fieldsStr.length());

	try {
		int id = std::stoi(idStr);

		if (id >= 0) {
			name = nameStr;
			type = SectionItem::typeFromName(typeStr.c_str());
			setId(id);
		} else {
			throw std::runtime_error("Invalid section item id");
		}
	}
	catch (std::exception e) {
		std::cout << "Section item Id is incorrect, or wrong format.";
		throw e;
	}
}

std::string SectionItem::getName() {
	return name;
}

void SectionItem::setName(std::string& name) {
	this->name = std::string(name);
}

SectionItem::Type SectionItem::getType() {
	return type;
}

void SectionItem::setType(SectionItem::Type& type) {
	this->type = Type(type);
}

