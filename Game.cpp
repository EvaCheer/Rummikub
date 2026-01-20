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
 * <functions related to the game logic and flow>
 *
 */
#include "Game.h"
#include "Player.h"

void initGame(Game& game)
{
	game.currentPlayer = 0;

	std::cout << "Enter number of players (2-4): ";
	std::cin >> game.playerCount;

	while (game.playerCount < 2 || game.playerCount > 4) {
		std::cout << "Invalid number. Enter 2-4: ";
		std::cin >> game.playerCount;
	}

	initTileSet(game.bag);
	tileSetShuffle(game.bag);

	game.players = new Player[game.playerCount];
	for (int i = 0; i < game.playerCount; i++) {
		initPlayer(game.players[i], game.bag);
	}

	initTable(game.table);
}

void freeGame(Game& game)
{
	delete[] game.players;
	game.players = nullptr;
}

void gameRun(Game& game)
{
	bool running = true;

	while (running) {
		Player& player = game.players[game.currentPlayer];

		std::cout << "\n--- Player "
			<< game.currentPlayer + 1
			<< "'s turn ---\n";

		gameHandleTurn(game, player);

		if (gameCheckWinAndPrintScore(game)) {
			running = false;
			break;
		}

		game.currentPlayer =
			(game.currentPlayer + 1) % game.playerCount;
	}
}

void gameHandleTurn(Game& game, Player& player)
{
	Player playerSnapshot;
	initPlayer(playerSnapshot);
	copyPlayer(playerSnapshot, player);

	Table tableSnapshot;
	initTable(tableSnapshot);
	copyTable(tableSnapshot, game.table);

	bool turnOver = false;
	bool hasPlacedTile = false;

	while (!turnOver) {
		printTable(game.table);

		std::cout << "Your hand:\n";
		playerPrintHand(player);

		gamePrintMenu();

		int choice;
		std::cin >> choice;

		switch (choice) {
		case 1:
			if (gameHandlePlaceTile(game, player))
				hasPlacedTile = true;
			break;

		case 2:
			if (gameHandlePlaceSequence(game, player))
				hasPlacedTile = true;
			break;

		case 3:
			gameHandleSplit(game);
			break;

		case 4:
			gameHandleMerge(game);
			break;

		case 5:
			//if table is invalid, you can't draw and end turn
			if (!tableIsValid(game.table)) {
				std::cout << "Table is invalid.\n";
				break;
			}
			playerDrawTile(player, game.bag);
			turnOver = true;
			break;

		case 6:
			//Finish turn
			//Rule: on the first turn, a player must put over 30 points on the table
			if (player.isFirstTurn) {
				int onTurnStart = playerHandScore(playerSnapshot);
				int onTurnEnd = playerHandScore(player);
				int pointsPlacedOnTable = onTurnStart - onTurnEnd;

				if (pointsPlacedOnTable >= 30 && tableIsValid(game.table)) {
					turnOver = true;
					player.isFirstTurn = false;
					break;
				}
				else if (pointsPlacedOnTable < 30) {
					std::cout << "You must put over 30 points on the table on your first turn." << std::endl;
					break;
				}
				else if (!tableIsValid(game.table)) {
					std::cout << "Table is invalid" << std::endl;
					break;
				}
			}
			else {
				if (gameCanFinishTurn(game, hasPlacedTile))
					turnOver = true;
				break;
			}

		case 7:
			copyPlayer(player, playerSnapshot);
			copyTable(game.table, tableSnapshot);
			hasPlacedTile = false;
			std::cout << "Turn reset.\n";
			break;

		case 8:
			playerSortHandByNumber(player);
			break;

		case 9:
			playerSortHandByColor(player);
			break;

		default:
			std::cout << "Invalid choice.\n";
		}
	}
}

bool gameHandlePlaceTile(Game& game, Player& player)
{
	int tileIndex;
	std::cout << "Select tile index: ";
	std::cin >> tileIndex;

	if (!playerIsValidIndex(player, tileIndex)) {
		std::cout << "Invalid index.\n";
		return false;
	}

	Tile tile = playerGetTile(player, tileIndex);

	int choice;
	std::cout << "1 - Existing sequence\n";
	std::cout << "2 - New sequence\n";
	std::cin >> choice;

	if (choice == 2) {
		tableAddSequenceWithTile(game.table, tile);
		playerRemoveFromHand(player, tileIndex);
		return true;
	}

	if (choice == 1) {
		int seqIndex, side;
		std::cout << "Sequence index: ";
		std::cin >> seqIndex;

		std::cout << "1 - Front\n2 - Back\n";
		std::cin >> side;

		bool success = false;
		if (side == 1)
			success = tablePlaceTileFront(game.table, seqIndex, tile);
		else if (side == 2)
			success = tablePlaceTileBack(game.table, seqIndex, tile);

		if (!success) {
			std::cout << "Invalid placement.\n";
			return false;
		}

		playerRemoveFromHand(player, tileIndex);
		return true;
	}

	return false;
}

bool gameHandlePlaceSequence(Game& game, Player& player)
{
	int size = 0;
	std::cout << "How long is the sequence?" << std::endl;
	std::cin >> size;

	if (size < 3)
	{
		std::cout << "A sequence must have at least 3 tiles.\n";
		return false;
	}

	int* indexes = new int[size];
	Sequence s;
	initSequence(s);
	std::cout << "Enter indexes in sequence order: ";

	for (int i = 0; i < size; i++)
	{
		int idx;
		std::cin >> idx;

		if (idx < 0 || idx >= playerGetSize(player))
		{
			std::cout << "Invalid index.\n";
			delete[] indexes;
			return false;
		}

		indexes[i] = idx;
		addBack(s, playerGetTile(player, idx));
	}
	if (!isValidSequence(s))
	{
		std::cout << "Sequence is not valid.\n";
		delete[] indexes;
		return false;
	}
	selectionSortDesc(indexes, size);
	for (int i = 0; i < size; i++)
	{
		playerRemoveFromHand(player, indexes[i]);
	}
	tableAddSequence(game.table, s);
	delete[] indexes;
	return true;
}

void gameHandleSplit(Game& game)
{
	int seqIndex, splitIndex;
	std::cout << "Sequence index: ";
	std::cin >> seqIndex;
	std::cout << "Split position: ";
	std::cin >> splitIndex;

	if (!tableSplitSequence(game.table, seqIndex, splitIndex))
		std::cout << "Invalid split.\n";
}

void gameHandleMerge(Game& game)
{
	int a, b;
	std::cout << "First index: ";
	std::cin >> a;
	std::cout << "Second index: ";
	std::cin >> b;

	if (!tableMergeSequences(game.table, a, b))
		std::cout << "Cannot merge.\n";
}

bool gameCanFinishTurn(const Game& game, bool hasPlacedTile)
{
	if (!hasPlacedTile) {
		std::cout << "You must place or draw.\n";
		return false;
	}

	if (!tableIsValid(game.table)) {
		std::cout << "Table is invalid.\n";
		return false;
	}

	return true;
}

bool gameCheckWinAndPrintScore(const Game& game)
{
	const Player& winner = game.players[game.currentPlayer];

	if (playerGetSize(winner) != 0)
		return false;

	std::cout << "Player "
		<< game.currentPlayer + 1
		<< " wins!\n";

	for (int i = 0; i < game.playerCount; i++) {
		int score = playerHandScore(game.players[i]);
		if (i == game.currentPlayer)
			std::cout << "Player " << i + 1 << ": 0 (winner)\n";
		else
			std::cout << "Player " << i + 1 << ": -" << score << "\n";
	}

	return true;
}

void gamePrintMenu()
{
	std::cout << "1 - Place tile\n";
	std::cout << "2 - Place sequence\n";
	std::cout << "3 - Split sequence\n";
	std::cout << "4 - Merge sequences\n";
	std::cout << "5 - Draw tile\n";
	std::cout << "6 - Finish turn\n";
	std::cout << "7 - Reset turn\n";
	std::cout << "8 - Sort by number\n";
	std::cout << "9 - Sort by color\n";
}

void selectionSortDesc(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++) {
		int maxIndex = i;
		for (int j = i + 1; j < n; j++)
			if (arr[j] > arr[maxIndex])
				maxIndex = j;

		int temp = arr[i];
		arr[i] = arr[maxIndex];
		arr[maxIndex] = temp;
	}
}

