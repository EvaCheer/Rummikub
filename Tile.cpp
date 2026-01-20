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
* <functions for tile initialization, access controls, utility>
*
*/
#include "Tile.h"
#include "ColorUtils.h"
#include <iostream>

void initTile(Tile& t) {
	t.color = Color::NONE;
	t.number = 0;
}

void initTile(Tile& t, Color c, int number) {
	if (number < 1 || number > 13) {
		throw "Tile number must be between 1 and 13";
	}
	t.color = c;
	t.number = number;
}

Color getTileColor(const Tile& t) {
	return t.color;
}

int getTileNumber(const Tile& t) {
	return t.number;
}

void printTile(const Tile& t) {
	std::cout << colorToAnsi(t.color)
		<< t.number
		<< "\033[0m";
}

