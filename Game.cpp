#include "Game.h"
#include "Player.h"

Game::Game() : playerCount(0), currentPlayer(0)
{
	std::cout << "Enter number of players (2-4): ";
	std::cin >> playerCount;

	while (playerCount < 2 || playerCount > 4) {
		std::cout << "Invalid number. Enter 2-4: ";
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
		Player& player = players[currentPlayer];
		//TODO clear screen?
		std::cout << "\n--- Player " << currentPlayer + 1 << "'s turn ---" << std::endl;
		//TODO print table
		handleTurn(player);
		currentPlayer = (currentPlayer + 1) % playerCount;
	}
}
void Game::printMenu() const
{
	std::cout << "1 - Place a tile" << std::endl;
	std::cout << "2 - Place a sequence" << std::endl;
	std::cout << "3 - Split table row" << std::endl;
	std::cout << "4 - Merge table rows" << std::endl;
	std::cout << "5 - Draw a tile" << std::endl;
	std::cout << "6 - Finish turn" << std::endl;
	std::cout << "7 - Reset turn" << std::endl;
	std::cout << "8 - Sort hand by number" << std::endl;
	std::cout << "9 - Sort hand by color" << std::endl;
}

void Game::handleTurn(Player& player)
{
	Player playerSnapshot = player;
	Table tableSnapshot = table;

	bool turnOver = 0;
	bool hasPlacedTile = 0;

	while (!turnOver) {
		table.print();
		std::cout << "Your hand: " << std::endl;
		player.printHand();
		printMenu();

		int choice;
		std::cin >> choice;

		switch (choice) {
		case 1:
			if (handlePlaceTile(player))
				hasPlacedTile = true;
			break;
		case 2:
			handlePlaceSequence(player);
			hasPlacedTile = true;
			break;
		case 3:
			handleSplit();
			break;
		case 4:
			handleMerge();
			break;
		case 5:
			//TODO: Add a winning condition: if the TileSet is empty
			player.drawATile(bag);
			turnOver = 1;
			break;
		case 6:
			if (canFinishTurn(hasPlacedTile))
				turnOver = true;
			break;
		case 7:
			player = playerSnapshot;
			table = tableSnapshot;
			hasPlacedTile = 0;
			std::cout << "Turn reset." << std::endl;
			break;
		case 8:
			player.sortHandByNumber();
			break;
		case 9:
			player.sortHandByColor();
			break;
		default:
			std::cout << "Invalid choice." << std::endl;
		}
	}
}

bool Game::handlePlaceTile(Player& player) {
	int tileIndex;
	std::cout << "Select tile index from hand: ";
	std::cin >> tileIndex;

	if (!player.isValidIndex(tileIndex)) {
		std::cout << "Invalid tile index." << std::endl;
		return false;
	}

	Tile tile = player.getTile(tileIndex);

	int choice;
	std::cout << "1 - Place on existing sequence" << std::endl;
	std::cout << "2 - Start new sequence" << std::endl;
	std::cin >> choice;

	if (choice == 2) {
		table.addSequence(tile);
		player.removeFromHand(tileIndex);
		return true;
	}

	if (choice == 1) {
		int seqIndex;
		std::cout << "Select sequence index: ";
		std::cin >> seqIndex;

		if (!table.isValidIndex(seqIndex)) {
			std::cout << "Invalid sequence index." << std::endl;
			return false;
		}

		int side;
		std::cout << "1 - Front" << std::endl; 
		std::cout << "2 - Back" << std::endl;
		std::cin >> side;

		bool success = 0;
		if (side == 1)
			success = table.placeTileFront(seqIndex, tile);
		else if (side == 2)
			success = table.placeTileBack(seqIndex, tile);
		else {
			std::cout << "Invalid input." << std::endl;
			return false;
		}
			
		if (!success) {
			std::cout << "Tile cannot be placed there." << std::endl;
			return false;
		}

		player.removeFromHand(tileIndex);
		return true;
	}

	std::cout << "Invalid option.\n";
	return false;
}

void Game::handleSplit()
{
	int seqIndex, splitIndex;
	std::cout << "Sequence index: ";
	std::cin >> seqIndex;
	std::cout << "Split position: ";
	std::cin >> splitIndex;

	if (!table.splitSequence(seqIndex, splitIndex)) {
		std::cout << "Invalid split.\n";
	}
}

void Game::handleMerge()
{
	int a, b;
	std::cout << "First sequence index: ";
	std::cin >> a;
	std::cout << "Second sequence index: ";
	std::cin >> b;

	if (!table.mergeSequences(a, b)) {
		std::cout << "Cannot merge these sequences.\n";
	}
}

bool Game::canFinishTurn(bool hasPlacedTile) const
{
	if (!hasPlacedTile) {
		std::cout << "You must place at least one tile or draw.\n";
		return false;
	}

	if (!table.isValid()) {
		std::cout << "Table is invalid.\n";
		return false;
	}

	return true;
}

bool Game::checkWinAndPrintScore() const
{

	const Player& winner = players[currentPlayer];

	if (winner.getSize() != 0)
		return false;

	std::cout << "Player " << currentPlayer + 1 << " wins!" << std::endl;

	std::cout << "Final scores: " << std::endl;

	for (int i = 0; i < playerCount; i++) {
		int score = players[i].handScore();

		if (i == currentPlayer) {
			std::cout << "Player " << i + 1 << ": 0 (winner)" << std::endl;
		}
		else {
			std::cout << "Player " << i + 1 << ": -" << score << std::endl;
		}
	}
	return true;
}

bool Game::handlePlaceSequence(Player& player) {
	int size = 0;
	std::cout << "How long is the sequence?" << std::endl;
	std::cin >> size;

	if (size < 3) {
		std::cout << "A sequence must have at least 3 tiles.\n";
		return false;
	}

	int* indexes = new int[size];
	Sequence s;
	std::cout << "Enter indexes in sequence order: ";

	for (int i = 0; i < size; i++) {
		int idx;
		std::cin >> idx;

		if (idx < 0 || idx >= player.getSize()) {
			std::cout << "Invalid index.\n";
			delete[] indexes;
			return false;
		}

		indexes[i] = idx;
		s.addBack(player.getTile(idx));
	}
	if (!s.isValid()) {
		std::cout << "Sequence is not valid.\n";
		delete[] indexes;
		return false;
	}
	selectionSortDesc(indexes, size);
	for (int i = 0; i < size; i++) {
		player.removeFromHand(indexes[i]);
	}
	table.addSequence(s);
	delete[] indexes;
	return true;

}

void Game::selectionSortDesc(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++) {
		int maxIndex = i;

		for (int j = i + 1; j < n; j++) {
			if (arr[j] > arr[maxIndex]) {
				maxIndex = j;
			}
		}

		int temp = arr[i];
		arr[i] = arr[maxIndex];
		arr[maxIndex] = temp;
	}
}