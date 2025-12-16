#include "TileSet.h"
#include <cstdlib>


TileSet::TileSet() {
	size = 0;
	initialize();
}

int TileSet::getSize() const {
	return size;
}
Tile TileSet::getTile(int index) const {
	return tiles[index];
}
void TileSet::initialize() {
	static const Color COLORS[] = { Color::RED, Color::BLUE, Color::YELLOW, Color::BLACK };

	for (Color c : COLORS) {
		for (int n = 1; n <= 13; n++) {
			tiles[size++] = Tile(c, n);
			tiles[size++] = Tile(c, n);
		}
	}
}


void TileSet::shuffle() {
	for (int i = size - 1; i > 0; i--) {
		int j = std::rand() % (i + 1);

		Tile temp = tiles[i];
		tiles[i] = tiles[j];
		tiles[j] = temp;
	}
}

//TODO: handle size = 0; tileSet isEmpty()
Tile TileSet::drawATile() {
	return tiles[--size];
}