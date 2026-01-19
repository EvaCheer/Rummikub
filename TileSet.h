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
* <TileSet header>
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

void shuffleTileSet(TileSet& set);
Tile tileSetDraw(TileSet& set);

