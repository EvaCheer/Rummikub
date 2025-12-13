#include <iostream>
#include "Headers.h"

int main()
{
	TileSet set;

	for (int i = 0; i < set.getSize(); i++) {
		set.getTile(i).print();
		std::cout << std::endl;
	}
}