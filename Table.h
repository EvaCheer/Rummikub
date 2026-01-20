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
* <Table struct and function declarations, related to handling>
* <the sequences on the table and validating the table>
*/
#pragma once
#include "Sequence.h"

#define MAX_TABLE_SEQUENCES 20

struct Table {
	Sequence sequences[MAX_TABLE_SEQUENCES];
	int size;
};

void initTable(Table& table);

void copyTable(Table& destTable, const Table& sourceTable);

int getTableSize(const Table& table);
const Sequence& getTableSequence(const Table& table, int index);
bool isValidTableIndex(const Table& table, int index);

void tableAddSequenceWithTile(Table& table, const Tile& tile);
void tableAddSequence(Table& table, const Sequence& seq);

bool tablePlaceTileFront(Table& table, int seqIndex, const Tile& tile);
bool tablePlaceTileBack(Table& table, int seqIndex, const Tile& tile);

bool tableSplitSequence(Table& table, int seqIndex, int splitIndex);
bool tableMergeSequences(Table& table, int first, int second);

bool tableIsValid(const Table& table);

void printTable(const Table& table);

