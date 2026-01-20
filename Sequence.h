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
* <Sequence struct and function declarations related to>
* <doing operations on a sequence of tiles>
*
*/
#pragma once
#include "Tile.h"

#define MAX_SEQUENCE_SIZE 13

struct Sequence {
	Tile sequence[MAX_SEQUENCE_SIZE];
	int size;
};

void initSequence(Sequence& seq);
void initSequenceWithTile(Sequence& seq, const Tile& tile);

int getSequenceSize(const Sequence& seq);
Tile getSequenceTile(const Sequence& seq, int index);

bool isRun(const Sequence& seq);
bool isGroup(const Sequence& seq);
bool isValidSequence(const Sequence& seq);

bool canAddFront(const Sequence& seq, const Tile& t);
bool canAddBack(const Sequence& seq, const Tile& t);
bool addFront(Sequence& seq, const Tile& t);
bool addBack(Sequence& seq, const Tile& t);

bool canMergeWith(const Sequence& seq1, const Sequence& seq2);
bool mergeSequences(Sequence& seq1, const Sequence& seq2);
Sequence splitSequence(Sequence& seq, int index);

void printSequence(const Sequence& seq);

