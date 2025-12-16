#include "Player.h"

Player::Player()
	: hand(nullptr), size(0), capacity(0)
{
}

Player::Player(TileSet& tileSet)
	: hand(new Tile[14]), size(0), capacity(14)
{
	for (int i = 0; i < 14; i++) {
		hand[size++] = tileSet.drawATile();
	}
}

void Player::resize()
{
	if (capacity == 0) capacity = 1;
	int newCapacity = 2 * capacity;
	Tile* resized = new Tile[newCapacity];

	for (int i = 0; i < size; i++) {
		resized[i] = hand[i];
	}
	
	capacity = newCapacity;
	delete[] hand;
	hand = resized;
}

void Player::copyFrom(const Player& p)
{
	capacity = p.capacity;
	size = p.size;
	hand = new Tile[capacity];
	for (int i = 0; i < size; i++) {
		hand[i] = p.hand[i];
	}
}

void Player::free()
{
	delete[] hand;
	hand = nullptr;
	size = 0;
	capacity = 0;
}


Player::Player(const Player& p)
{
	free();
	copyFrom(p);
}

Tile Player::getTile(int index) const
{
	if (index < 0 || index >= size) {
		throw "Invalid index when getting a tile from hand.";
	}
	return hand[index];
}

int Player::getSize() const
{
	return size;
}

Player& Player::operator=(const Player& p)
{
	if (&p != this) {
		free();
		copyFrom(p);
	}
	return *this;
}

Player::~Player()
{
	free();
}

void Player::drawATile(TileSet& tileSet)
{
	Tile newTile = tileSet.drawATile();
	if (size == capacity) {
		resize();
	}
	hand[size] = newTile;
	size++;
}

void Player::printHand() const
{
	for (int i = 0; i < size; i++) {
		hand[i].print();
		std::cout << " ";
	}
	std::cout << std::endl;
}

void Player::removeFromHand(int index)
{
	if (index < 0 || index >= size) {
		throw "Invalid index on removing a tile from hand.";
	}
	//put the last tile on the removed tile index
	//decrement the size
	hand[index] = hand[size - 1];
	size--;
}

int Player::handScore() const
{
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += hand[i].getNumber();
	}
	return sum;
}

bool Player::isValidIndex(int index) const
{
	return index >= 0 && index < size;
}
