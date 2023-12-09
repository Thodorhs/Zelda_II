#pragma once
#include <string>
#include <vector>
#include <sstream>
#define MAX_WIDTH  5000
#define MAX_HEIGHT 5000
typedef unsigned short Index;
typedef unsigned short Dim;
typedef std::vector<std::vector<Index>> TileMap;

static TileMap MapData(MAX_HEIGHT,std::vector<Index>(MAX_WIDTH,0));

void SetTile(Dim col, Dim row, Index index);
Index GetTile(Dim col, Dim row);

void WriteBinMap(const TileMap* m, FILE* fp);
bool ReadBinMap(TileMap* m, FILE* fp);

void WriteTextMap(const TileMap*, FILE* fp);
void ReadTextMap(const std::string path);

void ClearMap(void);

void print(void);
TileMap* GetMapData(void);

