#include "Tile.h"
#include "ColorUtils.h"
#include <iostream>

Tile::Tile() : color(Color::NONE), number(0) {}

Tile::Tile(Color c,int num) {
	if (num < 1 || num > 13) {
		throw "Tile number must be between 1 and 13";
	}
	number = num;
	color = c;
}


Color Tile::getColor() const {
	return color;
}
int Tile::getNumber() const {
	return number;
}


void Tile::print() const {
	std::cout << number << " " << colorToString(color);
}