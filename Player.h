#pragma once
#include "Tile.h"
#include "TileSet.h"
#include <iostream>

class Player {
	Tile* hand;
	int size;
	int capacity;

	void resize();
	void copyFrom(const Player& p);
	void free();
public:
	Player();
	Player(TileSet& tileSet);
	Player(const Player& p);
	Player& operator=(const Player & p);
	~Player();

	void drawATile(TileSet& tileSet);
	void printHand() const;
	void removeATile(int index);
};
