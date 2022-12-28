#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "../Include/App.h" 
void parse(app::Game game)
{
	std::string fname;
	std::cout << "Enter the file name: ";
	std::cin >> fname;


	std::vector<std::string> row;
	std::string line, word;

	std::fstream file(fname, std::ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();

			std::stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			game.update_content(row);
		}
	}
	else
		std::cout << "Could not open the file\n";



}
