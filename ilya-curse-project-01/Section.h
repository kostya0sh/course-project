#pragma once
#include "Entity.h"

class Section : public Entity {

public:

	Section(int id, const std::string& name) : Entity{ id }, name{ name } {}

	Section(int id) : Entity{ id } {}

	std::string toString();

	void fromString(std::string input);

	std::string getName();

	void setName(std::string& name);

private:
	std::string name;
};

