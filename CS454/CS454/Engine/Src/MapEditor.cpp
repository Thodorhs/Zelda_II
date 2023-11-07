#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../Include/MapEditor.h"
#include "../Include/Util/EngineDefines.h"

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
	
	std::string line, word;
	std::fstream file(path, std::ios::in);
	uint64_t line_idx = 0;
	uint64_t word_idx = 0;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			std::vector<Index> row(MAX_WIDTH, 0);

			std::stringstream str(line);

			while (getline(str, word, ',')) {
				row.insert(row.begin()+word_idx,stoi(word));
				word_idx++;
			}
			word_idx = 0;
			MapData.insert(MapData.begin() + line_idx, row);
			line_idx++;
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
	for (auto i = 0; i < Engine_Consts.map_rows; i++) {
		for (auto j = 0; j < Engine_Consts.map_cols; j++) {
			std::cout << MapData[i][j];
		}
		std::cout << std::endl;
	}
}

TileMap* GetMapData()
{ return &MapData; }