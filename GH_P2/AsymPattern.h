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
		AsymPattern(ArithSeq*, int size);
		~AsymPattern();

		void addArithSeq(int key, const ArithSeq&);
		ArithSeq* getArithSeq(int key);
		void setArithSeq(int p, int q, int key);
		void resetSeq(int key);

	private:
		ArithSeq** sequences_;
		int size_;

		bool seqExists(int key);
		bool atCapacity();
		const int MAX_CAPACITY = 10;
};

#endif