//
// Created by Jeremy on 1/21/25.
// h file for AsymPattern Implementation
//

#ifndef ASYMPATTERN_H
#define ASYMPATTERN_H

#include <map>
#include "ArithSeq.h"

using namespace std;

class AsymPattern {
	public:
		explicit AsymPattern(map<int, ArithSeq>);
		~AsymPattern();

		void addArithSeq(int, const ArithSeq&);
		ArithSeq getArithSeq(int);
		void removeArithSeq(int);
		void reset();

	private:
		map<int, ArithSeq> sequences;
		map<int, ArithSeq> originalSequences;
		bool seqExists(int);
		bool atCapacity();
		const int MAX_CAPACITY = 10;
};

#endif