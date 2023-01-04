#pragma once
#include <string>
#include <vector>
#include <sstream>

typedef unsigned short Index;
typedef unsigned short Dim;
typedef std::vector<std::vector<Index>> TileMap;


/* START UNIT 2*/
#define GRID_THIN_AIR_MASK 0x0000 // element is ignored
#define GRID_LEFT_SOLID_MASK 0x0001 // bit 0
#define GRID_RIGHT_SOLID_MASK 0x0002 // bit 1
#define GRID_TOP_SOLID_MASK 0x0004 // bit 2
#define GRID_BOTTOM_SOLID_MASK 0x0008 // bit 3
#define GRID_GROUND_MASK 0x0010 // bit 4, keep objects top / bottom (gravity)
#define GRID_FLOATING_MASK 0x0020 // bit 5, keep objects anywhere inside (gravity)
#define GRID_EMPTY_TILE GRID_THIN_AIR_MASK
#define GRID_SOLID_TILE \
(GRID_LEFT_SOLID_MASK | GRID_RIGHT_SOLID_MASK | GRID_TOP_SOLID_MASK | GRID_BOTTOM_SOLID_MASK)

#define GRID_ELEMENT_WIDTH 4
#define GRID_ELEMENT_HEIGHT 4
#if 16 % GRID_ELEMENT_WIDTH != 0
#error "TILE_WIDTH % GRID_ELEMENT_WIDTH must be zero!"
#endif
#if 16 % GRID_ELEMENT_HEIGHT != 0
#error "TILE_HEIGHT % GRID_ELEMENT_HEIGHT must be zero!"
#endif
#define GRID_BLOCK_COLUMNS (16 / GRID_ELEMENT_WIDTH)
#define GRID_BLOCK_ROWS (16 / GRID_ELEMENT_HEIGHT)
#define GRID_ELEMENTS_PER_TILE (GRID_BLOCK_ROWS * GRID_BLOCK_COLUMNS)
#define GRID_MAX_HEIGHT (240 * GRID_BLOCK_ROWS)
#define GRID_MAX_WIDTH (320 * GRID_BLOCK_COLUMNS)
typedef unsigned char byte;
using GridIndex = byte;

typedef GridIndex GridMap[GRID_MAX_WIDTH][GRID_MAX_HEIGHT];
static GridMap grid; // example of a global static grid
void SetGridTile(GridMap* m, Dim col, Dim row, GridIndex index);

#define GRID_BLOCK_SIZEOF \
(GRID_ELEMENTS_PER_TILE * sizeof(GridIndex))

#define DIV_GRID_ELEMENT_WIDTH(i) ((i)>>2)
#define DIV_GRID_ELEMENT_HEIGHT(i) ((i)>>2)
#define MUL_GRID_ELEMENT_WIDTH(i) ((i)<<2)
#define MUL_GRID_ELEMENT_HEIGHT(i) ((i)<<2)


/* END UNIT 2*/

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