#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../../../Engine/Include/MapEditor.h"

TileMap MapEditor::MapData;

void MapEditor::SetTile(Dim col, Dim row, Index index)
{ MapData[row][col] = index; }

Index MapEditor::GetTile(Dim col, Dim row)
{ return MapData[row][col]; }

void MapEditor::WriteBinMap(const TileMap* m, FILE* fp)
{ fwrite(m, sizeof(TileMap), 1, fp); }

bool MapEditor::ReadBinMap(TileMap* m, FILE* fp) {
	/* binary formatted read, like descent parsing */ 
	return true;
}

void MapEditor::WriteTextMap(const TileMap*, FILE* fp) {
	/* custom write in text format */
}

void MapEditor::ReadTextMap(const std::string path) {
	std::vector<Index> row;
	std::string line, word;
	std::fstream file(path, std::ios::in);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();

			std::stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(stoi(word));
			MapData.push_back(row);
		}
	}
	else std::cout << "Could not open the file\n";
}

void MapEditor::print() {
	for (auto it : MapData) {
		for (int i = 0; i < it.size(); i++) {
			std::cout << it[i];
		}
		std::cout << std::endl;
	}
}

TileMap* MapEditor::GetMapData()
{ return &MapData; }