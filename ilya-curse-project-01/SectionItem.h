#pragma once
#include "Entity.h"

static const char* typeNames[] = { "type1", "type2", "type3" };

class SectionItem: public Entity {

public:

	enum Type { type1, type2, type3 };

	static const char* typeName(int t) {
		return typeNames[t];
	}

	static Type typeFromName(const char* tName) {
		int i = 0;
		for (auto n : typeNames) {
			if (strcmp(n, tName) == 0) {
				return static_cast<Type>(i);
			}

			i++;
		}

		throw std::runtime_error("Item type not found");
	}

	SectionItem(int id, const std::string& name, const Type& type) : Entity{ id }, name{ name }, type{ type } {}

	SectionItem(int id) : Entity{ id } {}

	std::string toString();

	void fromString(std::string input);

	std::string getName();

	void setName(std::string& name);

	Type getType();

	void setType(Type& t);

private:

	std::string name;
	Type type;
};
