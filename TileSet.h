/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Zlatina Georgieva
* @idnumber 0MI0600109
* @compiler VC
*
* <TileSet struct that holds all tiles in the set>
* <forward declaration of functions for initialization, access and actions>
*
*/
#pragma once
#include "Tile.h"

struct TileSet {
	Tile tiles[104];
	int size;
};

void initTileSet(TileSet& set);

int getTileSetSize(const TileSet& set);
Tile getTileFromSet(const TileSet& set, int index);

void tileSetShuffle(TileSet& set);
Tile tileSetDraw(TileSet& set);

