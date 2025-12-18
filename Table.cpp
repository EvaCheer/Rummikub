#include "Table.h"
#include <iostream>

Table::Table() : size(0) {}

int Table::getSize() const
{
	return size;
}

const Sequence& Table::getSequence(int index) const
{
	return sequences[index];
}

void Table::addSequence(const Tile& tile)
{
	if (size >= 20) {
		throw "Table is full, cannot add more sequences.";
	}

	Sequence newSeq(tile);

	sequences[size++] = newSeq;
}

void Table::addSequence(const Sequence& s) {
	if (size >= 20) {
		throw "Table is full, cannot add more sequences.";
	}

	sequences[size++] = s;
}

bool Table::placeTileFront(int seqIndex, const Tile& t)
{
	if (seqIndex < 0 || seqIndex >= size)
		return false;
	return sequences[seqIndex].addFront(t);
}

bool Table::placeTileBack(int seqIndex, const Tile& t)
{
	if (seqIndex < 0 || seqIndex >= size)
		return false;
	return sequences[seqIndex].addBack(t);
}

bool Table::splitSequence(int seqIndex, int splitIndex)
{
	if (seqIndex < 0 || seqIndex >= size)
		return false;

	if (splitIndex <= 0 || splitIndex >= sequences[seqIndex].getSize())
		return false;

	if (size >= 20)
		return false;

	Sequence newSeq = sequences[seqIndex].split(splitIndex);

	sequences[size++] = newSeq;
	return true;
}

bool Table::mergeSequences(int first, int second)
{
	if (first < 0 || second < 0 ||
		first >= size || second >= size ||
		first == second)
		return false;

	// Merge second into first
	if (!sequences[first].mergeWith(sequences[second]))
		return false;

	// Remove second sequence
	for (int i = second; i < size - 1; i++) {
		sequences[i] = sequences[i + 1];
	}

	size--;
	return true;
}

bool Table::isValid() const
{
	for (int i = 0; i < size; i++) {
		if (!sequences[i].isValid()) return false;
	}
	return true;
}

bool Table::isValidIndex(int index) const
{
	return index >= 0 && index < size;
}

void Table::print() const
{
	for (int i = 0; i < size; i++) {
		std::cout << i << ".) ";
		sequences[i].print();
		std::cout << std::endl;
	}
}
