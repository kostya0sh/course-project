#pragma once
#include "Serializable.h"
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>

class Entity: public Serializable {

public:
	Entity(int id) : mId{ id }, Serializable {} {}

	virtual std::string toString() {
		return nullptr;
	}

	virtual void fromString(std::string input) {
		return;
	}

	int getId();

	void setId(int id);

private:

	int mId;
};

