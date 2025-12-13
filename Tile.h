#pragma once
#include "Color.h"

class Tile {
	Color color;
	int number;

public:
	Tile();
	Tile(Color c,int num);

	Color getColor() const;
	int getNumber() const;

	void print() const;
};

//class Joker : Tile {
//
//};
