#pragma once
#include "DbFile.h"
#include "Section.h"

class SectionsFile: public DbFile<Section> {

public:
	SectionsFile() : DbFile{ "stores.txt" } {}

	SectionsFile(const char* fileName) : DbFile{ fileName } {}

	virtual void create(Section& e) {
		int maxId = -1;
		for (auto r : content) {
			if (r.getId() > maxId) {
				maxId = r.getId();
			}
		}

		Section* created = new Section(++maxId, e.getName());
		content.push_back(*created);
	}

	virtual Section* deserializeLine(std::string line) {
		Section* s = new Section(-1);
		s->fromString(line);

		if (s->getId() >= 0) {
			return s;
		}

		return nullptr;
	}
};

