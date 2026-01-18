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
* <handles a tile>
*
*/
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
	std::cout << colorToAnsi(color)
		<< number
		<< "\033[0m";
}

Tile Tile::Joker() {
	Tile t;
	t.joker = true;
	return t;
}

bool Tile::isJoker() const {
	return joker;
}