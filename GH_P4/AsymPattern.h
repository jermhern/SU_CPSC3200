//
// Created by Jeremy on 1/21/25.
// h file for AsymPattern Implementation
//

#ifndef ASYMPATTERN_H
#define ASYMPATTERN_H

#include "ArithSeq.h"

using namespace std;

class AsymPattern {
	public:
		AsymPattern(ArithSeq*, int size = 10);
		AsymPattern(const AsymPattern&); // Copy Constructor
		AsymPattern(AsymPattern&& src); // move
		AsymPattern& operator=(const AsymPattern&); // Overloaded Assignment Operator
		AsymPattern& operator=(AsymPattern&&); // move
		~AsymPattern();

		void addArithSeq(int key, ArithSeq&);
		void setArithSeq(int p, int q, int key);
		void resetSeq(int key);
		bool seqExists(int key); // public query regarding state

	private:
		ArithSeq** sequences_;
		int size_;
		bool atCapacity();
		const int MAX_CAPACITY = 10;
		void copy(const AsymPattern& src);
};

#endif