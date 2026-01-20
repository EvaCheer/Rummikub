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
* <Operations on a sequence of tiles>
* <Validations>
*
*/
#include "Sequence.h"
#include <iostream>

void initSequence(Sequence& seq) 
{
	seq.size = 0;
}
void initSequenceWithTile(Sequence& seq, const Tile& tile) 
{
	seq.size = 1;
	seq.sequence[0] = tile;
}

int getSequenceSize(const Sequence& seq)
{
	return seq.size;
}
Tile getSequenceTile(const Sequence& seq, int index)
{
	if (index < 0 || index >= seq.size) {
		throw "Invalid index when getting a tile from sequence.";
	}
	return seq.sequence[index];
}
//same colors, a sequence of numbers
bool isRun(const Sequence& seq)
{
	if (seq.size < 2) return false;

	Color baseColor = getTileColor(seq.sequence[0]);
	for (int i = 1; i < seq.size; i++) {
		if (getTileColor(seq.sequence[i]) != baseColor ||
			getTileNumber(seq.sequence[i]) != getTileNumber(seq.sequence[i - 1]) + 1) {
			return false;
		}
	}
	return true;
}
//different colors, same numbers
bool isGroup(const Sequence& seq)
{
	if (seq.size < 2) return false;

	int baseNumber = getTileNumber(seq.sequence[0]);
	for (int i = 1; i < seq.size; i++) {
		if (getTileNumber(seq.sequence[i]) != baseNumber) return false;

		for (int j = 0; j < i; j++) {
			if (getTileColor(seq.sequence[i]) == getTileColor(seq.sequence[j])) 
				return false;
		}
	}
	return true;
}
bool isValidSequence(const Sequence& seq)
{
	if (seq.size < 3)
		return false;

	return isRun(seq) || isGroup(seq);
}

bool canAddFront(const Sequence& seq, const Tile& t)
{
	if (seq.size >= MAX_SEQUENCE_SIZE) return false;
	if (seq.size == 0) return true;

	if (seq.size == 1) {
		Tile a = seq.sequence[0];
		if ((getTileColor(t) == getTileColor(a) && getTileNumber(t) == getTileNumber(a) - 1) ||
			(getTileNumber(t) == getTileNumber(a) && getTileColor(t) != getTileColor(a))) {
			return true;
		}
		return false;
	}

	if (seq.size == 2) {
		Tile a = seq.sequence[0];
		Tile b = seq.sequence[1];

		if (getTileColor(a) == getTileColor(b)) { // run forming
			return getTileColor(t) == getTileColor(a) && getTileNumber(t) == getTileNumber(a) - 1;
		}
		if (getTileNumber(a) == getTileNumber(b)) { // group forming
			if (getTileNumber(t) != getTileNumber(a)) return false;
			if (getTileColor(t) == getTileColor(a) || getTileColor(t) == getTileColor(b)) return false;
			return true;
		}
		return false;
	}

	if (isRun(seq)) {
		return getTileColor(t) == getTileColor(seq.sequence[0]) &&
			getTileNumber(t) == getTileNumber(seq.sequence[0]) - 1;
	}

	if (isGroup(seq)) {
		if (getTileNumber(t) != getTileNumber(seq.sequence[0])) return false;
		for (int i = 0; i < seq.size; i++) {
			if (getTileColor(seq.sequence[i]) == getTileColor(t)) return false;
		}
		return true;
	}

	return false;
}
bool canAddBack(const Sequence& seq, const Tile& t)
{
	if (seq.size >= MAX_SEQUENCE_SIZE) return false;
	if (seq.size == 0) return true;

	if (seq.size == 1) {
		Tile a = seq.sequence[0];
		if ((getTileColor(t) == getTileColor(a) && getTileNumber(t) == getTileNumber(a) + 1) ||
			(getTileNumber(t) == getTileNumber(a) && getTileColor(t) != getTileColor(a))) {
			return true;
		}
		return false;
	}

	if (seq.size == 2) {
		Tile a = seq.sequence[0];
		Tile b = seq.sequence[1];

		if (getTileColor(a) == getTileColor(b)) { // run forming
			return getTileColor(t) == getTileColor(a) && getTileNumber(t) == getTileNumber(b) + 1;
		}
		if (getTileNumber(a) == getTileNumber(b)) { // group forming
			if (getTileNumber(t) != getTileNumber(a)) return false;
			if (getTileColor(t) == getTileColor(a) || getTileColor(t) == getTileColor(b)) return false;
			return true;
		}
		return false;
	}

	if (isRun(seq)) {
		return getTileColor(t) == getTileColor(seq.sequence[0]) &&
			getTileNumber(t) == getTileNumber(seq.sequence[seq.size - 1]) + 1;
	}

	if (isGroup(seq)) {
		if (getTileNumber(t) != getTileNumber(seq.sequence[0])) return false;
		for (int i = 0; i < seq.size; i++) {
			if (getTileColor(seq.sequence[i]) == getTileColor(t)) return false;
		}
		return true;
	}

	return false;
}
bool addFront(Sequence& seq, const Tile& t)
{
	if (!canAddFront(seq, t)) return false;

	for (int i = seq.size; i > 0; i--) {
		seq.sequence[i] = seq.sequence[i - 1];
	}
	seq.sequence[0] = t;
	seq.size++;
	return true;
}
bool addBack(Sequence& seq, const Tile& t)
{
	if (!canAddBack(seq, t)) return false;

	seq.sequence[seq.size++] = t;
	return true;
}

bool canMergeWith(const Sequence& seq1, const Sequence& seq2) 
{
	return seq1.size + seq2.size <= MAX_SEQUENCE_SIZE;
}
bool mergeSequences(Sequence& seq1, const Sequence& seq2) 
{
	if (!canMergeWith(seq1, seq2)) return false;
	for (int i = 0; i < seq2.size; i++) {
		seq1.sequence[seq1.size++] = seq2.sequence[i];
	}
	return true;
}
Sequence splitSequence(Sequence& seq, int index) 
{
	Sequence second;
	initSequence(second);

	for (int i = index; i < seq.size; i++) {
		second.sequence[second.size++] = seq.sequence[i];
	}

	seq.size = index;
	return second;
}

void printSequence(const Sequence& seq)
{
	for (int i = 0; i < seq.size; i++) {
		printTile(seq.sequence[i]);
		std::cout << " ";
	}
	std::cout << std::endl;
}