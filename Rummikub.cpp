#include <iostream>
#include "Headers.h"

int main()
{
	TileSet set;
	set.shuffle();
	Player p1(set);
	Player p2(set);

	for (int i = 0; i < set.getSize(); i++) {
		set.getTile(i).print();
		std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << "Player 1 hand: ";
	p1.printHand();
	std::cout << "Player 2 hand: ";
	p2.printHand();
}