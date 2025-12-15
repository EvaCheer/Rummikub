#include "Game.h"

Game::Game() : playerCount(0), currentPlayer(0)
{
	std::cout << "Enter number of players (2–4): ";
	std::cin >> playerCount;

	while (playerCount < 2 || playerCount > 4) {
		std::cout << "Invalid number. Enter 2–4: ";
		std::cin >> playerCount;
	}

	bag.shuffle();
	players = new Player[playerCount];

	for (int i = 0; i < playerCount; i++) {
		players[i] = Player(bag);
	}
}

Game::~Game()
{
	delete[] players;
	players = nullptr;
}

void Game::run()
{
	bool running = true;
	while (running) {
		Player player = players[currentPlayer];
		std::cout << "\n--- Player " << currentPlayer + 1 << "'s turn ---" << std::endl;

		handleTurn(player);
		currentPlayer = (currentPlayer + 1) % playerCount;
	}
}

void Game::handleTurn(Player& player)
{
	int turnOver = 0;
	while (!turnOver) {
		printMenu();
		int choice;
		std::cin >> choice;

		switch (choice) {
		case 1:
			player.drawATile(bag);
			std::cout << "You drew a tile."<<std::endl;
			turnOver = 1;
			break;
		case 2:
			std::cout << "plays a tile";
			break;
		case 3:
			player.printHand();
			break;
		case 4:
			turnOver = 1;
			break;
		default:
			std::cout << "Invalid choice." << std::endl;
		}
	}

}

void Game::printMenu() const
{
	std::cout << "1 - Draw a tile" << std::endl;
	std::cout << "2 - Play a tile(later)" << std::endl;
	std::cout << "3 - Show hand" << std::endl;
	std::cout << "4 - End turn" << std::endl;
}
