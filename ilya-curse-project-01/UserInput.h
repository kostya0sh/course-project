#pragma once

#include <iostream>
#include "Database.h"
#include "Circle.h"


class UserInput {

public:
	static void start() {
		Database db = Database();

		circle<std::string> menuOptions = circle<std::string>();
		menuOptions.push("Params format - :<r - region id/s - store id/sc - section id>/<item;fields;exmaple>");
		menuOptions.push("1 - show all");
		menuOptions.push("2 - show with params");
		menuOptions.push("3 - add");
		menuOptions.push("4 - remove");
		menuOptions.push("5 - revert");
		menuOptions.push("6 - manual command");
		menuOptions.push("7 - exit");


		db.load();

		while (true) {
			showMenuOptions(menuOptions);

			std::string input = std::string();
			std::getline(std::cin, input);

			system("CLS");

			//exit
			if (input == "7") {
				break;
			}

			//show all
			if (input == "1") {
				db.exec("find/");
			}

			//show with params
			if (input == "2") {
				input.clear();
				std::cout << "Enter command: " << "find/";
				std::getline(std::cin, input);
			}

			//add
			if (input == "3") {
				input.clear();
				std::cout << "Enter command: " << "add/";
				std::getline(std::cin, input);
			}

			//remove
			if (input == "4") {
				input.clear();
				std::cout << "Enter command: " << "remove/";
				std::getline(std::cin, input);
			}

			//revert
			if (input == "5") {
				db.exec("revert");
			}

			//manual command
			if (input == "6") {
				std::cout << "Enter command: ";
				input.clear();
				std::getline(std::cin, input);
				db.exec(input.c_str());
			}
			
		}

		db.flush();
	}

	static void showMenuOptions(circle<std::string>& menuOptions) {
		auto iterator = menuOptions.raw_first();
		std::cout << "\n--------------" << std::endl;
		for (int i = 0; i < menuOptions.size(); i++) {
			std::cout << iterator->v << std::endl;
			iterator = iterator->next;
		}

		std::cout << "--------------" << std::endl;
	}
};