//
// Created by Jeremy on 1/21/25.
// h file for AsymPattern Implementation
//

#ifndef ASYMPATTERN_H
#define ASYMPATTERN_H

#include <map>
#include "ArithSeq.h";

class AsymPattern {

	public:
		ArithSeq();
		~ArithSeq();

		void addArithSeq(int, const ArithSeq&);
		ArithSeq* getArithSeq(int);
		void removeArithSeq(int);

	private:
		map<int, ArithSeq> sequences;
};

#endif