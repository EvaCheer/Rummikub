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
* <Player struct and function declarations related to>
* <handling a hand of Tiles>
*
*/
#pragma once
#include "Tile.h"
#include "TileSet.h"
#include <iostream>

struct Player {
	Tile* hand;
	int size;
	int capacity;
	bool isFirstTurn;
};

void initPlayer(Player& player);
void initPlayer(Player& player, TileSet& tileSet);
void freePlayer(Player& player);
void copyPlayer(Player& dest, const Player& src);

Tile playerGetTile(const Player& player, int index);
int playerGetSize(const Player& player);

void playerDrawTile(Player& player, TileSet& tileSet);
void playerPrintHand(const Player& player);
void playerRemoveFromHand(Player& player, int index);
int playerHandScore(const Player& player);
bool playerIsValidIndex(const Player& player, int index);

void playerSortHandByColor(Player& player);
void playerSortHandByNumber(Player& player);

void resizePlayer(Player& player);
