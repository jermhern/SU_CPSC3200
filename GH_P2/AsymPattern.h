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

	private:
		map<int, ArithSeq> sequences;
		bool seqExists(int);
};

#endif