#pragma once
#include "Entity.h"

class Region: public Entity {

public:

	Region(int id, const std::string& name) : Entity { id }, name { name } {}

	Region(int id) : Entity { id } {}

	std::string toString();

	void fromString(std::string input);

	std::string getName();

	void setName(std::string& name);

private: 

	std::string name;

};

