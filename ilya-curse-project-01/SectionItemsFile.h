#pragma once
#include "DbFile.h"
#include "SectionItem.h"

class SectionItemsFile : public DbFile<SectionItem> {

public:
	SectionItemsFile() : DbFile{ "section_items.txt" } {}

	SectionItemsFile(const char* fileName) : DbFile{ fileName } {}

	virtual void create(SectionItem& e) {
		int maxId = -1;
		for (auto r : content) {
			if (r.getId() > maxId) {
				maxId = r.getId();
			}
		}

		SectionItem* created = new SectionItem(++maxId, e.getName(), e.getType());
		content.push_back(*created);
	}

	virtual SectionItem* deserializeLine(std::string line) {
		SectionItem* s = new SectionItem(-1);
		s->fromString(line);

		if (s->getId() >= 0) {
			return s;
		}

		return nullptr;
	}
};

