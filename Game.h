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
 * <Game struct and functions declaration related to the game logic and flow>
 *
 */
#pragma once

#include "TileSet.h"
#include "Player.h"
#include "Table.h"

struct Game {
	TileSet bag;
	Player* players;
	Table table;
	int playerCount;
	int currentPlayer;
};

void initGame(Game& game);
void freeGame(Game& game);

void gameRun(Game& game);
void gameHandleTurn(Game& game, Player& player);

bool gameHandlePlaceTile(Game& game, Player& player);
bool gameHandlePlaceSequence(Game& game, Player& player);
void gameHandleSplit(Game& game);
void gameHandleMerge(Game& game);

bool gameCanFinishTurn(const Game& game, bool hasPlacedTile);
bool gameCheckWinAndPrintScore(const Game& game);
void gamePrintMenu();

void selectionSortDesc(int* arr, int n);

