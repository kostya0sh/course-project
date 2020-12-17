#pragma once
#include <vector>
#include "Entity.h"

template<class T>
class DbFile {

public:

	DbFile(const char* fileName): fileName { fileName } {}

	void load() {
		std::string line;
		std::fstream fileR(fileName, std::ios::in);

		if (fileR.is_open()) {
			while (getline(fileR, line)) {
				T* t = deserializeLine(line);
				if (t) {
					content.push_back(*t);
				}
			}
			fileR.close();
		}
		else {
			std::cout << "Unable to open file, creating new one..." << std::endl;
			std::fstream tempW(fileName, std::ios::out);
			tempW.close();
			std::cout << "Created new file >> " << fileName << std::endl;
		}
	}

	void flush() {
		std::fstream rFileW(fileName, std::ios::out | std::ios::trunc);
		if (!rFileW.is_open()) {
			std::cout << "Unable to open file, creating new one..." << std::endl;
			std::fstream tempW(fileName, std::ios::out);
			tempW.close();
			std::cout << "Created new file >> " << fileName << std::endl;
		}

		for (auto item : content) {
			rFileW << item.toString();
		}
	}

	std::vector<T>* getAll() {
		return new std::vector<T>(content);
	}

	T* findById(int id) {
		int i = 0;
		for (auto item : content) {
			if (item.getId() == id) {
				return &(content.at(i));
			}
			i++;
		}

		return nullptr;
	}

	void deleteById(int id) {
		int i = 0;
		for (auto item : content) {
			if (item.getId() == id) {
				content.erase(content.begin() + i);
				return;
			}
			i++;
		}
	}

	virtual void create(T& e) {
		
	}

	virtual T* deserializeLine(std::string line) {
		return nullptr;
	}

	const char* fileName;

protected:

	std::vector<T> content = std::vector<T>();
};

