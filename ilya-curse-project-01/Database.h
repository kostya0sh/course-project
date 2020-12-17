#pragma once
#include "RegionsFile.h"
#include "StoresFile.h"


class Database {

public:

	~Database() {
		for (auto i : findResults) {
			if (i->r) delete i->r;
			if (i->s) delete i->s;
			delete i;
		}

		for (auto i : getAllResults) {
			delete i;
		}
	}

	struct FindResult {
		Region* r;
		Store* s;
	};

	void addRegion(const char* name) {
		RegionsFile rf = RegionsFile();
		rf.load();

		Region r = Region(-1, name);
		rf.create(r);

		rf.flush();
	}

	std::vector<FindResult*>* getAllRegions() {
		RegionsFile rf = RegionsFile();
		rf.load();

		std::vector<FindResult*>* ret = buildGetAllResult();

		std::vector<Region> regions = *rf.getAll();
		for (auto r : regions) {
			Region* copy = new Region(r.getId(), r.getName());
			FindResult* fr = buildFindResult(copy, nullptr);
			ret->push_back(fr);
		}		

		return ret;
	}

	FindResult* findRegion(int id) {
		RegionsFile rf = RegionsFile();
		rf.load();

		Region* found = rf.findById(id);

		if (found) {
			Region* copy = new Region(found->getId(), found->getName());
			FindResult* res = buildFindResult(copy, nullptr);
			return res;
		}

		return nullptr;
	}

	void addStore(int regionId, const char* name) {
		RegionsFile rf = RegionsFile();
		rf.load();

		Region* r = rf.findById(regionId);

		if (!r) {
			throw std::runtime_error("Can not create Store, invalid Region id");
		}

		std::string sfName = "r" + std::to_string(r->getId()) + ".txt";
		StoresFile sf = StoresFile(sfName.c_str());
		sf.load();

		Store s = Store(-1, name);
		sf.create(s);

		sf.flush();
	}

	FindResult* findStore(int regionId, int storeId) {
		FindResult* rr = findRegion(regionId);

		if (rr) {
			std::string sfName = "r" + std::to_string(rr->r->getId()) + ".txt";
			StoresFile sf = StoresFile(sfName.c_str());
			sf.load();

			Store* s = sf.findById(storeId);
			if (s) {
				Store* copy = new Store(s->getId(), s->getName());
				FindResult* res = buildFindResult(rr->r, copy);
				return res;
			}
		}

		return nullptr;
	}

	std::vector<FindResult*>* getAllStores() {
		RegionsFile rf = RegionsFile();
		rf.load();

		std::vector<FindResult*>* ret = buildGetAllResult();

		std::vector<Region> regions = *rf.getAll();
		for (auto r : regions) {
			Region* copy = new Region(r.getId(), r.getName());
			FindResult* fr = buildFindResult(copy, nullptr);


			ret->push_back(fr);
		}

		return ret;
	}

private:

	std::vector<void*> getAllResults = std::vector<void*>();
	std::vector<FindResult*> findResults = std::vector<FindResult*>();

	FindResult* buildFindResult(Region* r, Store* s) {
		FindResult* fr = new FindResult();
		fr->r = r;
		fr->s = s;

		findResults.push_back(fr);
		return fr;
	}

	std::vector<FindResult*>* buildGetAllResult() {
		std::vector<FindResult*>* res = new std::vector<FindResult*>();
		getAllResults.push_back(res);
		return res;
	}
};

