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
* <Tile header>
*
*/
#pragma once
#include "Color.h"

struct Tile {
	Color color;
	int number;
};

void initTile(Tile& t);
void initTile(Tile& t, Color c, int number);

Color getTileColor(const Tile& t);
int getTileNumber(const Tile& t);

void printTile(const Tile& t);

