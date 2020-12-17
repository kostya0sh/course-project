#pragma once
#include "Region.h"
#include "DbFile.h"

class RegionsFile: public DbFile<Region> {

public:

	RegionsFile() : DbFile { "regions.txt" } {}

	virtual void create(Region& e) {
		int maxId = -1;
		for (auto r : content) {
			if (r.getId() > maxId) {
				maxId = r.getId();
			}
		}

		Region* created = new Region(++maxId, e.getName());
		content.push_back(*created);
	}

	virtual Region* deserializeLine(std::string line) {
		Region* s = new Region(-1);
		s->fromString(line);

		if (s->getId() >= 0) {
			return s;
		}

		return nullptr;
	}
};

