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
* <main file>
*
*/

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
 * <main function, starts the game>
 *
 */
#include <iostream>
#include <ctime>
#include "Headers.h"

int main()
{
	std::srand(std::time(nullptr));
	Game game;
	initGame(game);
	gameRun(game);
	freeGame(game);
	return 0;

}