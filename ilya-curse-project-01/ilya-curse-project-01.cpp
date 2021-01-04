// ilya-curse-project-01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "UserInput.h"

int main() {
	while (true) {
		try {
			UserInput::start();
			break;
		} catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}