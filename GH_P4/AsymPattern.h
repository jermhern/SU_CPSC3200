//
// Updated by Jeremy on 3/2/25.
// h file for AsymPattern Implementation
//

#ifndef ASYMPATTERN_H
#define ASYMPATTERN_H

#include <iostream>
#include "ArithSeq.h"

using namespace std;

class AsymPattern: public ArithSeq {
	public:
		AsymPattern(ArithSeq*, int size);
		AsymPattern(const AsymPattern&); // Copy Constructor
		AsymPattern(AsymPattern&& src); // move
		~AsymPattern();

		void replicate(ArithSeq&);
		void reset() override;

		void addArithSeq(ArithSeq&, int key);
		void setArithSeq(int p, int q, int key);
		void resetSeq(int key);
		bool seqExists(int key); // public query regarding state

		// operator overloading
		bool operator==(const AsymPattern&);
		bool operator!=(const AsymPattern&);
		void operator++() override;
		void operator++(int) override;
		void operator--() override;
		void operator--(int) override;
		shared_ptr<int[]> operator[](int);
		friend ostream& operator<<(ostream&, const AsymPattern&);

	private:
		shared_ptr<ArithSeq[]> sequences_;
		shared_ptr<ArithSeq[]> originalSequences_;

		int size_;
		int originalSize_;
		bool atCapacity();
		const int MAX_CAPACITY = 10;
		void copy(const AsymPattern& src);

		// Suppress copying
		AsymPattern& operator=(const AsymPattern&); // Overloaded Assignment Operator
		AsymPattern& operator=(AsymPattern&&); // move
};

#endif