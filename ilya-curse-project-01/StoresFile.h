#pragma once
#include "DbFile.h"
#include "Store.h"

class StoresFile : public DbFile<Store> {

public:

	StoresFile() : DbFile { "stores.txt" } {}

	StoresFile(const char* fileName) : DbFile { fileName } {}

	virtual void create(Store& e) {
		int maxId = -1;
		for (auto r : content) {
			if (r.getId() > maxId) {
				maxId = r.getId();
			}
		}

		Store* created = new Store(++maxId, e.getName());
		content.push_back(*created);
	}

	virtual Store* deserializeLine(std::string line) {
		Store* s = new Store(-1);
		s->fromString(line);

		if (s->getId() >= 0) {
			return s;
		}

		return nullptr;
	}

};

