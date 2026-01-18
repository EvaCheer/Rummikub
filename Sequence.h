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
* <Sequence header>
*
*/
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
