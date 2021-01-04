#pragma once

#include <iostream>
#include "Database.h"


class UserInput {

public:
	static void start() {
		Database db = Database();

		db.load();

		while (true) {
			std::cout << "Enter command: ";

			std::string input = std::string();
			std::getline(std::cin, input);

			if (input == "exit") {
				break;
			}

			db.exec(input.c_str());
		}

		db.flush();
	}
};