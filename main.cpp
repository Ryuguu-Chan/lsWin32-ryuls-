#include <iostream>

// RUNS ON C++17 !!!
// compiler used: Visual Studio C++ compiler
#include <filesystem>

#include <Windows.h> // WIN32_FILE_ATTRIBUTE_DATA 

#include <string>

// TODO: essayer 

#include "Compute.h"
#include "appStrings.h"
#include "Actions.h"


namespace filesystem = std::filesystem;

int main(int argc, char** argv) {

	filesystem::path currentWorkingDirectory;

	if (argc == 1) {
		currentWorkingDirectory = filesystem::current_path();
	}
	else {
		// TODO: prendre en compte les options
		if (filesystem::exists(argv[1])) {
			if (filesystem::is_directory(argv[1])) {
				currentWorkingDirectory = argv[1];
			}
			else {
				std::cout << appStrings::NOT_A_DIRECTORY_ERROR_STR << std::endl;
				return EXIT_FAILURE;
			}
		}
		else {
			//std::cout << appStrings::DOES_NOT_EXIST_ERROR_STR << std::endl;

			// debug
			std::cout << argv[1] << std::endl;
			
			if (Actions::SHOW_ALL_DIRECTORIES(argv[1])) {

				std::cout << "show everything!!" << std::endl;
				
				if (argc == 2) {
					currentWorkingDirectory = filesystem::current_path();
				}
				for (auto const& dir_entry : filesystem::directory_iterator { currentWorkingDirectory }) {
					if (dir_entry.path().filename().generic_string()[0] != '~' && dir_entry.path().filename().generic_string()[0] == '$') {
						std::cout << dir_entry.path().filename().generic_string() << std::endl;
					}
					std::cout << dir_entry.path().filename().generic_string() << std::endl;
				}

				return EXIT_SUCCESS;
			}
			else if (Actions::SHOW_ALL_FILE_AUTHOR(argv[1])) {

				std::cout << "show the authors!!" << std::endl;
				
				for (auto const& dir_entry : filesystem::directory_iterator { currentWorkingDirectory }) {

					std::cout << dir_entry.path().filename().generic_string() << '\t';
					std::cout << "some attributes..." << std::endl;
				}

				return EXIT_SUCCESS;
			}
			else {
				std::cout << "error";
			}

			return EXIT_FAILURE;
		}
	}

	for (auto const& dir_entry : filesystem::directory_iterator{ currentWorkingDirectory }) {
		std::cout << dir_entry.path().filename().generic_string() << std::endl;
	}

	std::cout << std::endl;

	return EXIT_SUCCESS;
}