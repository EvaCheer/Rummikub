#pragma once
#include "Sequence.h"

class Table {
	Sequence sequences[20];
	int size;

public:
	Table();


	int getSize() const;
	const Sequence& getSequence(int index) const;

	//to add a row we must always initiate it with a tile
	void addSequence(const Tile& tile);
	void addSequence(const Sequence& s);
	bool placeTileFront(int seqIndex, const Tile& t);
	bool placeTileBack(int seqIndex, const Tile& t);

	bool splitSequence(int seqIndex, int sliceIndex);
	bool mergeSequences(int first, int second);

	bool isValid() const;
	bool isValidIndex(int index) const;

	void print() const;
};
