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
* <handles the deck of tiles>
*
*/
#include "TileSet.h"
#include <cstdlib>

static void initialize(TileSet& set) {
	static const Color COLORS[] = {
		Color::RED,
		Color::BLUE,
		Color::YELLOW,
		Color::BLACK
	};

	set.size = 0;

	for (Color c : COLORS) {
		for (int n = 1; n <= 13; n++) {
			initTile(set.tiles[set.size++], c, n);
			initTile(set.tiles[set.size++], c, n);
		}
	}
}

void initTileSet(TileSet& set) {
	initialize(set);
}

int getTileSetSize(const TileSet& set) {
	return set.size;
}

Tile getTileFromSet(const TileSet& set, int index) {
	return set.tiles[index];
}

void shuffleTileSet(TileSet& set) {
	for (int i = set.size - 1; i > 0; i--) {
		int j = std::rand() % (i + 1);

		Tile temp = set.tiles[i];
		set.tiles[i] = set.tiles[j];
		set.tiles[j] = temp;
	}
}

Tile tileSetDraw(TileSet& set) {
	// TODO: handle end of set
	return set.tiles[--set.size];
}
