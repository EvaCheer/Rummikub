#pragma once
#include "Tile.h"

class TileSet {
	Tile tiles[104];
	int size;


public:
	TileSet();

	int getSize() const;
	Tile getTile(int index) const;

private:
	void initialize();
};
