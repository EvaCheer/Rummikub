#pragma once
#include "Tile.h"

class Sequence {
	Tile sequence[13];
	int size;

public:
	Sequence();
	Sequence(const Tile& tile);

	int getSize() const;
	Tile getTile(int index) const;
	bool isValid() const;

	//TODO: alter for JOKER tile
	bool canAddFront(const Tile& t) const;
	bool canAddBack(const Tile& t) const;
	bool canMergeWith(const Sequence& other) const;
	bool addFront(const Tile& t);
	bool addBack(const Tile& t);
	bool mergeWith(const Sequence& other);
	Sequence split(int index);

	void print() const;

private:
	bool isRun() const;
	bool isGroup() const;
};
