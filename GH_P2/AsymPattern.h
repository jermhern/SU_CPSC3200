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
		AsymPattern(ArithSeq*);
		~AsymPattern();

		void addArithSeq(int, const ArithSeq&);
		ArithSeq* getArithSeq(int);
		void removeArithSeq(int);
		void resetAllSeq();

	private:
		ArithSeq* sequences_;
		int size_;

		bool seqExists(int);
		bool atCapacity();
		const int MAX_CAPACITY = 10;
};

#endif