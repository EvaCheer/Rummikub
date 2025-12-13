#include "TileSet.h"

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