#pragma once
#include "Entity.h"

class Store : public Entity {

public:
	Store(int id, const std::string& name) : Entity{ id }, name{ name } {}

	Store(int id) : Entity{ id } {}

	std::string toString();

	void fromString(std::string input);

	std::string getName();

	void setName(std::string& name);

private: 
	std::string name;
};

