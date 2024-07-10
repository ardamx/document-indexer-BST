#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

#include "WordBSTIndex.h"

int main()
{
	std::cout << "Indexing started..." << std::endl;
	clock_t t0, t1;
	std::string directory_path = "./test_docs";
	t0 = clock();

	WordBSTIndex wix = WordBSTIndex();
	std::regex word_regex("[a-z]+"); // regular expression for word extraction
	std::sregex_iterator words_end; // initialized here to save initialization computing in each loop

	try {
		for (const auto& entry : std::filesystem::directory_iterator(directory_path)) {
			std::string str;
			std::string filepath = entry.path().string();
			std::string filename = entry.path().filename().string();
			size_t filesize;

			std::ifstream file(filepath, std::ios::in | std::ios::ate);
			filesize = file.tellg();
			str.reserve(filesize);
			file.seekg(0);
			for (char c; file.get(c); )
			{
				// if it's uppercase char, lower it
				if (c >= 'A' && c <= 'Z') {
					str += c + 32;
				}
				else {
					str += c;
				}
			}

			// iterator over the matches
			std::sregex_iterator words_begin(str.begin(), str.end(), word_regex);
			for (std::sregex_iterator it = words_begin; it != words_end; ++it) {
				std::smatch match = *it;
				wix.Insert(match.str(), filename);
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	t1 = clock();
	std::cout << "Indexed in " << (double)(t1 - t0) / CLOCKS_PER_SEC << " seconds." << std::endl;

	while (true) {
		int option;
		std::cout << "1. Enter a single keyword to list the document(s)(file names)" << std::endl;
		std::cout << "2. Print the top 10 words that appeared most frequently" << std::endl;
		std::cout << "3. Print the top 10 words that appeared least frequently" << std::endl;
		std::cout << "4. Exit" << std::endl;
		std::cout << ">> ";
		std::cin >> option;

		if (option == 1) {
			std::string word;
			std::cout << "Enter word:" << std::endl;
			std::cout << ">> ";
			std::cin >> word;

			wix.SelectWhere(wix.root, word);
		}
		else if (option == 2) {
			wix.SelectTop10Desc();
		}
		else if (option == 3) {
			wix.SelectTop10Asc();
		}
		else if (option == 4) {
			break;
		}
		else {
			std::cout << "Invalid selection" << std::endl;
		}
	}
}
