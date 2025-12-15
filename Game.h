#pragma once
#include "TileSet.h"
#include "Player.h"

class Game {
	TileSet bag;
	Player* players;
	int playerCount;
	int currentPlayer;

public:
	Game();
	~Game();

	void run();
	void handleTurn(Player& player);
	void printMenu() const;

};
