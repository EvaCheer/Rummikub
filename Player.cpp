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
* <handing a hand of Tiles>
*
*/
#include "TileSet.h"
#include "Player.h"

#include <iostream>

void initPlayer(Player& player) 
{
	player.hand = nullptr;
	player.size = 0;
	player.capacity = 0;
	player.isFirstTurn = true;
}
void initPlayer(Player& player, TileSet& tileSet) {
	player.capacity = 14;
	player.size = 0;
	player.isFirstTurn = true;
	player.hand = new Tile[player.capacity];

	for (int i = 0; i < 14; i++) {
		Tile t = tileSetDraw(tileSet);
		player.hand[player.size] = t;
		player.size++;
	}
}

void freePlayer(Player& player) 
{
	delete[] player.hand;
	player.hand = nullptr;
	player.size = 0;
	player.capacity = 0;
	player.isFirstTurn = 0;
}
void copyPlayer(Player& dest, const Player& src)
{
	dest.capacity = src.capacity;
	dest.size = src.size;
	dest.isFirstTurn = src.isFirstTurn;
	dest.hand = new Tile[dest.capacity];

	for (int i = 0; i < dest.size; i++) {
		dest.hand[i].color = src.hand[i].color;
		dest.hand[i].number = src.hand[i].number;
	}
}

void resizePlayer(Player& player)
{
	if (player.capacity == 0) {
		player.capacity = 1;
	}

	int newCapacity = 2 * player.capacity;
	Tile* resized = new Tile[newCapacity];

	for (int i = 0; i < player.size; i++) {
		resized[i].color = player.hand[i].color;
		resized[i].number = player.hand[i].number;
	}

	delete[] player.hand;
	player.hand = resized;
	player.capacity = newCapacity;
}

Tile playerGetTile(const Player& player, int index)
{
	if (index < 0 || index >= player.size) {
		throw "Invalid index when getting a tile from hand.";
	}
	return player.hand[index];
}
int playerGetSize(const Player& player)
{
	return player.size;
}

void playerDrawTile(Player& player, TileSet& tileSet)
{
	if (player.size == player.capacity) {
		resizePlayer(player);
	}

	player.hand[player.size++] = tileSetDraw(tileSet);
}
void playerPrintHand(const Player& player)
{
	for (int i = 0; i < player.size; i++) {
		std::cout << i << " ";
		if (getTileNumber(player.hand[i]) > 9 && i < 10) {
			std::cout << " ";
		}
	}
	std::cout << std::endl;

	for (int i = 0; i < player.size; i++) {
		printTile(player.hand[i]);
		std::cout << " ";
		if (i > 9 && getTileNumber(player.hand[i]) < 10) {
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}

void playerRemoveFromHand(Player& player, int index)
{
	if (index < 0 || index >= player.size) {
		throw "Invalid index on removing a tile from hand.";
	}

	player.hand[index] = player.hand[player.size - 1];
	player.size--;
}
int playerHandScore(const Player& player)
{
	int sum = 0;
	for (int i = 0; i < player.size; i++) {
		sum += getTileNumber(player.hand[i]);
	}
	return sum;
}
bool playerIsValidIndex(const Player& player, int index)
{
	return index >= 0 && index < player.size;
}

void playerSortHandByColor(Player& player) {
	for (int i = 0; i < player.size - 1; i++) {
		int minIndex = i;

		for (int j = i + 1; j < player.size; j++) {
			if ((int)getTileColor(player.hand[j]) <
				(int)getTileColor(player.hand[minIndex])) {
				minIndex = j;
			}
			else if (getTileColor(player.hand[j]) ==
				getTileColor(player.hand[minIndex]) &&
				getTileNumber(player.hand[j]) <
				getTileNumber(player.hand[minIndex])) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			Tile temp = player.hand[i];
			player.hand[i] = player.hand[minIndex];
			player.hand[minIndex] = temp;
		}
	}
}

void playerSortHandByNumber(Player& player)
{
	for (int i = 0; i < player.size - 1; i++) {
		int minIndex = i;

		for (int j = i + 1; j < player.size; j++) {
			if (getTileNumber(player.hand[j]) <
				getTileNumber(player.hand[minIndex])) {
				minIndex = j;
			}
			else if (getTileNumber(player.hand[j]) ==
				getTileNumber(player.hand[minIndex]) &&
				(int)getTileColor(player.hand[j]) <
				(int)getTileColor(player.hand[minIndex])) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			Tile temp = player.hand[i];
			player.hand[i] = player.hand[minIndex];
			player.hand[minIndex] = temp;
		}
	}
}

