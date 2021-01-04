#pragma once
#include "RegionsFile.h"
#include "StoresFile.h"
#include "SectionsFile.h"
#include "SectionItemsFile.h"


class Database {

public:

	~Database() {
	
	}

	enum QueryItemType { REGION, STORE, SECTION, ITEM, NONE };

	struct Query {
		int regionId;
		int storeId;
		int sectionId;
		std::string cmd;
		QueryItemType itemType = NONE;
		SectionItem item;
		Region region;
		Store store;
		Section section;
	};

	struct IdNamePair {
		std::string id;
		std::string name;
	};

	struct FItem {
		int sectionId;
		SectionItemsFile* items;
	};

	struct FSection {
		SectionsFile* section;
		int storeId;
		std::vector<FItem*> items;
	};

	struct FStore {
		StoresFile* store;
		int regionId;
		std::vector<FSection*> sections;
	};

	struct FRegion {
		RegionsFile* region;
		std::vector<FStore*> stores;
	};

	void load() {
		FRegion* fRegion = new FRegion();
		fRegion->region = new RegionsFile();
		fRegion->region->load();

		auto allRegions = fRegion->region->getAll();
		for (auto r : *allRegions) {
			std::string sfName = "r" + std::to_string(r.getId()) + ".txt";
			FStore* fStore = new FStore();
			fStore->regionId = r.getId();
			fRegion->stores.push_back(fStore);
		    (*fStore).store = new StoresFile(sfName.c_str());
			fStore->store->load();

			auto allStores = fStore->store->getAll();
			for (auto s : *allStores) {
				std::string scfName = sfName.substr(0, sfName.length() - 4) + "_s" + std::to_string(s.getId()) + ".txt";
				FSection* fSection = new FSection();
				fSection->storeId = s.getId();
				fStore->sections.push_back(fSection);
				fSection->section = new SectionsFile(scfName.c_str());
				fSection->section->load();

				auto allSections = fSection->section->getAll();
				for (auto sc : *allSections) {
					std::string siName = scfName.substr(0, scfName.length() - 4) + "_sc" + std::to_string(sc.getId()) + ".txt";
					FItem* fItem = new FItem();
					fItem->sectionId = sc.getId();
					fSection->items.push_back(fItem);

					fItem->items = new SectionItemsFile(siName.c_str());
					
					fItem->items->load();
				}
			}
		}

		loaded = fRegion;
	}

	void flush() {
		loaded->region->flush();

		for (auto fStore: loaded->stores) {
			fStore->store->flush();

			for (auto fSection: fStore->sections) {
				fSection->section->flush();

				for (auto fItem : fSection->items) {
					fItem->items->flush();
				}
			}
		}
	}

	void exec(const char* query) {
		Query q = parseQuery(query);

		if (q.cmd == "find") {
			find(q);
		}

		if (q.cmd == "add") {
			addItem(q, query);
		}

		if (q.cmd == "remove") {
			removeItem(q, query);
		}
	}

	void removeItem(Query q, const char* rawQuery) {
		auto regions = loaded->region->getAll();

		if (q.itemType == REGION) {
			loaded->region->deleteById(q.region.getId());
			return;
		}

		for (auto fStore : loaded->stores) {
			if (q.regionId >= 0 && fStore->regionId != q.regionId) {
				continue;
			}

			auto stores = fStore->store->getAll();

			if (q.itemType == STORE) {
				fStore->store->deleteById(q.store.getId());
				return;
			}

			for (auto fSection : fStore->sections) {
				if (q.storeId >= 0 && fSection->storeId != q.storeId) {
					continue;
				}

				auto sections = fSection->section->getAll();

				if (q.itemType == SECTION) {
					fSection->section->deleteById(q.section.getId());
					return;
				}

				for (auto fItem : fSection->items) {
					if (q.sectionId >= 0 && fItem->sectionId != q.sectionId) {
						continue;
					}

					fItem->items->deleteById(q.item.getId());
					return;
				}
			}
		}
	}

	void addItem(Query q, const char* rawQuery) {
		auto regions = loaded->region->getAll();

		bool added = false;

		if (q.itemType == REGION) {
			loaded->region->create(q.region);
			added = true;
		}

		for (auto fStore : loaded->stores) {
			if (added) {
				break;
			}

			if (q.regionId >= 0 && fStore->regionId != q.regionId) {
				continue;
			}

			auto stores = fStore->store->getAll();
			
			if (q.itemType == STORE) {
				fStore->store->create(q.store);
				added = true;
				break;
			}

			for (auto fSection : fStore->sections) {
				if (added) {
					break;
				}

				if (q.storeId >= 0 && fSection->storeId != q.storeId) {
					continue;
				}

				auto sections = fSection->section->getAll();

				if (q.itemType == SECTION) {
					fSection->section->create(q.section);
					added = true;
					break;
				}

				for (auto fItem : fSection->items) {
					if (added) {
						break;
					}

					if (q.sectionId >= 0 && fItem->sectionId != q.sectionId) {
						continue;
					}
				
				
					fItem->items->create(q.item);
					added = true;
					break;
				}
			}
		}

		flush();
		load();
	}

	void find(Query q) {
		auto regions = loaded->region->getAll();
		print("Regions:", 0);
		print(*regions, 1);

		for (auto fStore : loaded->stores) {
			if (q.regionId >= 0 && fStore->regionId != q.regionId) {
				continue;
			}

			auto stores = fStore->store->getAll();
			std::string header = "Stores[region->" + std::to_string(fStore->regionId) + "]:";
			print(header.c_str(), 1);
			print(*stores, 2);

			for (auto fSection : fStore->sections) {
				if (q.storeId >= 0 && fSection->storeId != q.storeId) {
					continue;
				}

				auto sections = fSection->section->getAll();
				std::string header = "Sections[store->" + std::to_string(fSection->storeId) + "]:";
				print(header.c_str(), 2);
				print(*sections, 3);

				for (auto fItem : fSection->items) {
					if (q.sectionId >= 0 && fItem->sectionId != q.sectionId) {
						continue;
					}

					auto items = fItem->items->getAll();
					std::string header = "Items[section->" + std::to_string(fItem->sectionId) + "]:";
					print(header.c_str(), 3);
					for (auto item : *items) {
						if (q.item.getId() >= 0 && q.item.getId() != item.getId()) {
							continue;
						}

						if (!q.item.getName().empty() && q.item.getName() != item.getName()) {
							continue;
						}

						if (q.item.getType() >= 0 && q.item.getType() != item.getType()) {
							continue;
						}

						print(item, 4);
					}
					
				}
			}
		}
	}

	void print(const char* str, int level) {
		for (int i = 0; i < level; i++) {
			std::cout << "   ";
		}

		std::cout << str;

		if (str[strlen(str) - 1] != '\n') {
			std::cout << std::endl;
		} 
	}

	template<class T>
	void print(T& e, int level) {
		print(e.toString().c_str(), level);
	}

	template<class T>
	void print(std::vector<T> list, int level) {
		for (auto e : list) {
			print(e, level);
		}
	}

private:

	Query parseQuery(const char* query) {
		std::string q = std::string(query);

		if (q.empty()) {
			throw std::exception("Unknown command");
		}

		std::string cmdStr = q.substr(0, q.find("/"));

		if (cmdStr != "add" && cmdStr != "remove" && cmdStr != "find") {
			throw std::exception("Unknown command");
		}

		std::string paramsStr = q.substr(q.find("/") + 1, q.length());

		auto rPos = paramsStr.find(":r");
		auto sPos = paramsStr.find(":s");
		auto scPos = paramsStr.find(":sc");
		auto endPos = paramsStr.find("/");

		std::string regionIdStr = "-1";
		if (rPos != std::string::npos) {
			if (sPos != std::string::npos) {
				regionIdStr = paramsStr.substr(rPos + 2, sPos - rPos - 2);
			}
			else {
				regionIdStr = paramsStr.substr(rPos + 2, endPos - rPos - 2);
			}
		}
		else {
			std::string itemFields = "";
			IdNamePair pair = IdNamePair{ "-1", "" };
			pair = parseIdName(paramsStr);

			Region r = Region(std::stoi(pair.id), pair.name);
			return Query{
			-1,
			-1,
			-1,
			cmdStr,
			REGION,
			SectionItem(-1),
			r,
			Store(-1),
			Section(-1),
			};
		}

		std::string storeIdStr = "-1";
		if (sPos != std::string::npos) {
			if (scPos != std::string::npos) {
				storeIdStr = paramsStr.substr(sPos + 2, scPos - sPos - 2);
			}
			else {
				storeIdStr = paramsStr.substr(sPos + 2, endPos - sPos - 2);
			}
		}
		else {
			std::string itemFields = "";
			IdNamePair pair = IdNamePair{ "-1", "" };
			if (endPos != std::string::npos) {
				itemFields = paramsStr.substr(endPos + 1, q.length() - endPos);
				pair = parseIdName(itemFields);
			}

			Store s = Store(std::stoi(pair.id), pair.name);

			return Query{
			std::stoi(regionIdStr),
			-1,
			-1,
			cmdStr,
			STORE,
			SectionItem(-1),
			Region(-1),
			s,
			Section(-1),
			};
		}

		std::string sectionIdStr = "-1";
		if (scPos != std::string::npos) {
			if (endPos != std::string::npos) {
				sectionIdStr = paramsStr.substr(scPos + 3, endPos - scPos - 3);
			}
			else {
				sectionIdStr = paramsStr.substr(scPos + 3, endPos - scPos - 3);
			}
		}
		else {
			std::string itemFields = "";
			IdNamePair pair = IdNamePair{ "-1", "" };
			if (endPos != std::string::npos) {
				itemFields = paramsStr.substr(endPos + 1, q.length() - endPos);
				pair = parseIdName(itemFields);
			}

			Section sc = Section(std::stoi(pair.id), pair.name);

			return Query{
			std::stoi(regionIdStr),
			std::stoi(storeIdStr),
			-1,
			cmdStr,
			SECTION,
			SectionItem(-1),
			Region(-1),
			Store(-1),
			sc,
			};
		}

		std::string itemFields = "";
		SectionItem si = SectionItem(-1);
		if (endPos != std::string::npos) {
			itemFields = paramsStr.substr(endPos + 1, q.length() - endPos);
			si = parseItem(itemFields);
		}


		return Query{
			std::stoi(regionIdStr),
			std::stoi(storeIdStr),
			std::stoi(sectionIdStr),
			cmdStr,
			ITEM,
			si,
			Region(-1),
			Store(-1),
			Section(-1),
		};
	}

	SectionItem parseItem(std::string item) {
		try {
			auto firstDPos = item.find(";");

			if (firstDPos == std::string::npos) {
				return SectionItem(std::stoi(item));
			}

			std::string idStr = item.substr(0, firstDPos);
			if (idStr.empty()) {
				idStr = "-1";
			}
			auto sectionItem = SectionItem(std::stoi(idStr));

			std::string fieldsStr = item.substr(firstDPos + 1, item.length());

			if (fieldsStr.length() <= 0) {
				return sectionItem;
			}

			auto secondDPos = fieldsStr.find(";");

			if (secondDPos == std::string::npos) {
				std::string nameStr = fieldsStr.substr(0, secondDPos);
				sectionItem.setName(nameStr);
			}
			else {
				std::string nameStr = fieldsStr.substr(0, fieldsStr.find(";"));
				std::string typeStr = fieldsStr.substr(fieldsStr.find(";") + 1, fieldsStr.length());
				sectionItem.setName(nameStr);

				try {
					SectionItem::Type t = SectionItem::typeFromName(typeStr.c_str());
					sectionItem.setType(t);
				}
				catch (std::exception e) {
					SectionItem::Type t = SectionItem::Type::type1;
					sectionItem.setType(t);
				}
			}

			return sectionItem;			
		}
		catch (std::exception e) {
			std::cout << "Provided invalid item param for query" << std::endl;
			return SectionItem(-1);
		}
	}

	IdNamePair parseIdName(std::string item) {
		try {
			auto dPos = item.find(";");

			if (dPos == std::string::npos) {
				std::stoi(item);
				return IdNamePair{ item, "" };
			}

			std::string idStr = item.substr(0, dPos);
			if (idStr.empty()) {
				idStr = "-1";
			}

			std::string nameStr = item.substr(dPos + 1, item.length());
			return IdNamePair{ idStr, nameStr };
		}
		catch (std::exception e) {
			std::cout << "Invalid id/name pair" << std::endl;
			return IdNamePair{ "-1", "" };
		}
	}


	FRegion* loaded;
};

