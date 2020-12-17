#pragma once
#include <string>

class Serializable {

public:

	Serializable() {}

	virtual std::string toString() {
		return nullptr;
	}

	virtual Serializable* fromString(std::string& input) {
		return nullptr;
	}

};

