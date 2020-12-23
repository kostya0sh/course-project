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

	db.load();

	db.exec("add/;region_test_add_0");
	db.exec("add/:r0/;store_test_add_0");
	db.exec("add/:r0:s0/;section_test_add_0");
	db.exec("add/:r0:s0:sc0/;item_test_add_0;type3");
	db.exec("find/");
	db.exec("find/:r0:s0:sc0/;;type3");
	db.exec("find/:r0:s0:sc0/;;type1");
	db.exec("find/:r1");
	db.exec("remove/:r0:s0:sc0/0;;");
	db.exec("remove/:r0:s0/0;");
	db.exec("remove/:r0/0;");
	db.exec("remove/0;");

	db.flush();

	return 0;
}