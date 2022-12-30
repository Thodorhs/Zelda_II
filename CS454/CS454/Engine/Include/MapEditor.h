#pragma once
#include <string>
#include <vector>
#include <sstream>

typedef unsigned short Index;
typedef unsigned short Dim;
typedef std::vector<std::vector<Index>> TileMap;

class MapEditor {
	private:
		static TileMap MapData;

	public:
		void SetTile(Dim col, Dim row, Index index);
		Index GetTile(Dim col, Dim row);

		void WriteBinMap(const TileMap* m, FILE* fp);
		bool ReadBinMap(TileMap* m, FILE* fp);

		void WriteTextMap(const TileMap*, FILE* fp);
		void ReadTextMap(const std::string path);

		void print(void);
		TileMap* GetMapData(void);
};