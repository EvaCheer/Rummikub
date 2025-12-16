#include "Sequence.h"
#include <iostream>

Sequence::Sequence() : size(0)
{
}

Sequence::Sequence(const Tile& tile)
{
	size = 1;
	sequence[0] = tile;
}

int Sequence::getSize() const
{
	return size;
}

Tile Sequence::getTile(int index) const
{
	if (index<0 || index>size) {
		throw "Invalid index when getting a tile from sequence.";
	}
	return sequence[index];
}

//same colors, a sequence of numbers
bool Sequence::isRun() const {
	if (size < 2) return false;

	Color baseColor = sequence[0].getColor();

	for (int i = 1; i < size; i++) {
		if (sequence[i].getColor() != baseColor ||
			sequence[i].getNumber() != sequence[i - 1].getNumber() + 1) {
			return false;
		}
	}
	return true;
}

//different colors, same numbers
bool Sequence::isGroup() const {
	if (size < 2) return false;

	int baseNumber = sequence[0].getNumber();

	for (int i = 1; i < size; i++) {
		if (sequence[i].getNumber() != baseNumber)
			return false;

		for (int j = 0; j < i; j++) {
			if (sequence[i].getColor() == sequence[j].getColor())
				return false;
		}
	}
	return true;
}


bool Sequence::isValid() const
{
	if (size < 3)
		return false;

	return isRun() || isGroup();
}

bool Sequence::canAddFront(const Tile& t) const
{
	if (size >= 13)
		return false;

	if (size == 0)
		return true;

	if (size == 1) {
		const Tile& a = sequence[0];
		//Can become run
		if (t.getColor() == a.getColor() &&
			t.getNumber() == a.getNumber() - 1)
			return true;

		//Can become group
		if (t.getNumber() == a.getNumber() &&
			t.getColor() != a.getColor())
			return true;

		return false;
	}

	if (size == 2) {
		const Tile& a = sequence[0];
		const Tile& b = sequence[1];

		//Run forming
		if (a.getColor() == b.getColor()) {
			return t.getColor() == a.getColor() &&
				t.getNumber() == a.getNumber() - 1;
		}

		// Group forming
		if (a.getNumber() == b.getNumber()) {
			if (t.getNumber() != a.getNumber())
				return false;

			if (t.getColor() == a.getColor() ||
				t.getColor() == b.getColor())
				return false;

			return true;
		}

		return false;
	}

	if (isRun()) {
		return t.getColor() == sequence[0].getColor() &&
			t.getNumber() == sequence[0].getNumber() - 1;
	}

	if (isGroup()) {
		if (t.getNumber() != sequence[0].getNumber())
			return false;

		for (int i = 0; i < size; i++) {
			if (sequence[i].getColor() == t.getColor())
				return false;
		}
		return true;
	}

	return false;
}


bool Sequence::canAddBack(const Tile& t) const
{
	if (size >= 13)
		return false;
	if (size == 0) return true;

	//if the sequence is a run, the new tile must be the same color
	//and it needs to me 1 digit bigger than last tile
	if (isRun()) {
		return t.getColor() == sequence[0].getColor() &&
			t.getNumber() == sequence[size - 1].getNumber() + 1;
	}

	//if the sequence is a group, the new tile must be a different color
	//and the same number as any other tile
	if (isGroup()) {
		if (t.getNumber() != sequence[0].getNumber())
			return false;

		for (int i = 0; i < size; i++) {
			if (sequence[i].getColor() == t.getColor())
				return false;
		}
		return true;
	}

	return false;
}

bool Sequence::addFront(const Tile& t)
{
	if (!canAddFront(t))
		return false;

	// shift right
	for (int i = size; i > 0; i--) {
		sequence[i] = sequence[i - 1];
	}

	sequence[0] = t;
	size++;
	return true;
}

bool Sequence::addBack(const Tile& t)
{
	if (!canAddBack(t))
		return false;

	sequence[size] = t;
	size++;
	return true;
}

bool Sequence::canMergeWith(const Sequence& other) const
{
	return size + other.size <= 14;
}

bool Sequence::mergeWith(const Sequence& other)
{
	if (!canMergeWith(other))
		return false;

	for (int i = 0; i < other.size; i++) {
		sequence[size++] = other.sequence[i];
	}

	return true;
}


Sequence Sequence::split(int index) {
	Sequence second;

	for (int i = index; i < size; i++) {
		second.sequence[second.size++] = sequence[i];
	}

	size = index;
	return second;
}


void Sequence::print() const {
	for (int i = 0; i < size; i++) {
		sequence[i].print();
		std::cout << " ";
	}
}


