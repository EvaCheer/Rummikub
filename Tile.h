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

class Tile {
	Color color;
	int number;
	bool joker;

public:
	Tile();
	Tile(Color c,int num);
	static Tile Joker();

	Color getColor() const;
	int getNumber() const; 
	bool isJoker() const;

	void print() const;
};

//class Joker : Tile {
//
//};
