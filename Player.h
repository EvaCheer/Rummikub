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
* <Player header>
*
*/
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
	Tile getTile(int index) const;
	int getSize() const;
	Player& operator=(const Player & p);
	~Player();

	void drawATile(TileSet& tileSet);
	void printHand() const;
	void removeFromHand(int index);
	int handScore() const;
	bool isValidIndex(int index) const;
	void sortHandByColor();
	void sortHandByNumber();
};
