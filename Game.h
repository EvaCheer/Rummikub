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
* <Game headers>
*
*/
#pragma once
#include "TileSet.h"
#include "Player.h"
#include "Table.h"

class Game {
	TileSet bag;
	Player* players;
	Table table;
	int playerCount;
	int currentPlayer;

public:
	Game();
	~Game();

	void run();
	void handleTurn(Player& player);
	bool handlePlaceTile(Player& player);
	void handleSplit();
	void handleMerge();
	bool canFinishTurn(bool hasPlacedTile) const;

	bool checkWinAndPrintScore() const;


	void printMenu() const;


	bool handlePlaceSequence(Player& player);
	void selectionSortDesc(int* arr, int n);
};
