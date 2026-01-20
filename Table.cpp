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
* <handling the sequences on the table and validating the table>
*
*
*/
#include "Table.h"
#include <iostream>

void initTable(Table& table) 
{
	table.size = 0;
}

void copyTable(Table& dest, const Table& src) {
	dest.size = src.size;
	for (int i = 0; i < src.size; i++) {
		tableAddSequence(dest, src.sequences[i]);
	}
}

int getTableSize(const Table& table) 
{
	return table.size;
}

const Sequence& getTableSequence(const Table& table, int index) 
{
	if (index < 0 || index >= table.size) {
		throw "Invalid index when getting sequence from table.";
	}
	return table.sequences[index];
}

bool isValidTableIndex(const Table& table, int index) 
{
	return index >= 0 && index < table.size;
}

void tableAddSequenceWithTile(Table& table, const Tile& tile) 
{
	if (table.size >= MAX_TABLE_SEQUENCES) {
		throw "Table is full, cannot add more sequences.";
	}

	Sequence seq;
	initSequenceWithTile(seq, tile);
	table.sequences[table.size++] = seq;
}

void tableAddSequence(Table& table, const Sequence& seq) {
	if (table.size >= MAX_TABLE_SEQUENCES) {
		throw "Table is full, cannot add more sequences.";
	}

	table.sequences[table.size++] = seq;
}

bool tablePlaceTileFront(Table& table, int seqIndex, const Tile& tile) {
	if (!isValidTableIndex(table, seqIndex))
		return false;

	return addFront(table.sequences[seqIndex], tile);
}

bool tablePlaceTileBack(Table& table, int seqIndex, const Tile& tile) {
	if (!isValidTableIndex(table, seqIndex))
		return false;

	return addBack(table.sequences[seqIndex], tile);
}

bool tableSplitSequence(Table& table, int seqIndex, int splitIndex) {
	if (!isValidTableIndex(table, seqIndex))
		return false;

	Sequence& seq = table.sequences[seqIndex];

	if (splitIndex <= 0 || splitIndex >= seq.size)
		return false;

	if (table.size >= MAX_TABLE_SEQUENCES)
		return false;

	Sequence newSeq = splitSequence(seq, splitIndex);
	table.sequences[table.size++] = newSeq;

	return true;
}

bool tableMergeSequences(Table& table, int first, int second) {
	if (!isValidTableIndex(table, first) ||
		!isValidTableIndex(table, second) ||
		first == second)
		return false;

	if (!mergeSequences(table.sequences[first], table.sequences[second]))
		return false;

	// Remove second sequence (shift left)
	for (int i = second; i < table.size - 1; i++) {
		table.sequences[i] = table.sequences[i + 1];
	}

	table.size--;
	return true;
}

bool tableIsValid(const Table& table) {
	for (int i = 0; i < table.size; i++) {
		if (!isValidSequence(table.sequences[i]))
			return false;
	}
	return true;
}

void printTable(const Table& table) {
	for (int i = 0; i < table.size; i++) {
		std::cout << i << ".) ";
		printSequence(table.sequences[i]);
	}
}