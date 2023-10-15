#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../Include/MapEditor.h"


void SetTile(Dim col, Dim row, Index index)
{ MapData[row][col] = index; }

Index GetTile(Dim col, Dim row)
{ return MapData[row][col]; }

void WriteBinMap(const TileMap* m, FILE* fp)
{ fwrite(m, sizeof(TileMap), 1, fp); }

bool ReadBinMap(TileMap* m, FILE* fp) {
	/* binary formatted read, like descent parsing */ 
	return true;
}

void WriteTextMap(const TileMap*, FILE* fp) {
	/* custom write in text format */
}



void ReadTextMap(const std::string path) {
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

void ClearMap() {
	for (auto it : MapData)
		it.clear();

	MapData.clear();
}

void print() {
	for (auto it : MapData) {
		for (int i = 0; i < it.size(); i++) {
			std::cout << it[i];
		}
		std::cout << std::endl;
	}
}

TileMap* GetMapData()
{ return &MapData; }