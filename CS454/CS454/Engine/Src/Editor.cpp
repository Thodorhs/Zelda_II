#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../include/Editor.h"
using namespace MapEditor;

void Editor::update_content(std::vector<std::string> v) {
	content.push_back(v);
}

void Editor::print() {
	for (auto it : content) {
		for (int i = 0; i < it.size(); i++) {
			std::cout << it[i];
		}
		std::cout << std::endl;
	}
}


void Editor::parse(const std::string path) {
	std::vector<std::string> row;
	std::string line, word;
	std::fstream file(path, std::ios::in);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();

			std::stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			update_content(row);
		}
	}
	else
		std::cout << "Could not open the file\n";

}