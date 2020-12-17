// ilya-curse-project-01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Region.h"
#include "Database.h"
#include "RegionsFile.h"
#include "StoresFile.h"

int main() {
    std::cout << "Beginning...\n\n";
	Database db = Database();

	std::vector<Region*>* regions = db.getAllRegions();

	std::cout << "Regions:\n";
	for (auto r : *regions) {
		std::cout << "\t" << r->toString();
	}

	/*db.addStore(0, "store1");
	db.addStore(0, "store2");*/

	return 0;
}