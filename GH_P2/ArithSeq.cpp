//
// Created by Jeremy on 1/17/25.
//

/*
    Class Invariants:
    1. Setting the maximum number of operations for Arith Seq must be at least 30,
        which will be set automatically within the constructor if a valid value is not given.
    2. The length of the ArithSeq must always be greater than 0. The constructor will
        throw an error if an invalid length value (0 => n) is given.
    3. A valid difference for the construction of the object, and for the modify method, This prevents
        an invalid sequence to form, or no changes to be made.
    4. The original sequence value is used to keep track of the sequence before any operations can be made.
        This is required in order to return the sequence to its original state after Reset().
    5. In order to get the Kth value from an ArithSeq object the value k that is passed into the method must
       be larger than 0 and less than the sequence length, or an invalid argument exception will be thrown.
    6. In order to return the integer of values divisible by an integer, divisor parameter into the method must
       not equal 0, or divide by zero exception will be thrown.
*/

#include "ArithSeq.h"
#include <stdexcept>
#include <utility>

using namespace std;

// Constructor
ArithSeq::ArithSeq(int firstTerm, int difference, int sequenceLength, int maxOp) {

    if (sequenceLength <= 0) {
        throw invalid_argument("Sequence length must be greater than or equal to 0");
    }

    if (maxOp < 0) {
        throw invalid_argument("Max operations must be greater than 0");
    }

    if (difference <= 0) {
        throw invalid_argument("Difference must be greater than 0");
    }

    // validated inputs, set fields
    a1 = firstTerm;
    dst = difference;
    n = sequenceLength;
    maxOperations = maxOp;

    sequence = new int[n];
    // calculate each term of the sequence
    for (int i = 0; i < n; i++)
    {
        sequence[i] = a1 + i * dst;
    }

    // shallow copy
    originalSequence = new int[n];
    for (int i = 0; i < n; i++)
    {
        originalSequence[i] = sequence[i];
    }

    operations = 0;
}

// Destructor
ArithSeq::~ArithSeq() {
    delete[] sequence;
    delete[] originalSequence;
}

// Private utility function for copy
void ArithSeq::copy(const ArithSeq& src) {
    a1 = src.a1;
    dst = src.dst;
    n = src.n;
    maxOperations = src.maxOperations;
    operations = 0; // new objects will be set to 0

    sequence = new int[n];
    for (int i = 0; i < n; i++) {
        sequence[i] = src.sequence[i];
    }

    originalSequence = new int[n];
    for (int i = 0; i < n; i++) {
        originalSequence[i] = src.originalSequence[i];
    }
}

// Overloaded Assignment Operator
ArithSeq &ArithSeq::operator=(const ArithSeq& src) {
    if (this == &src) { return *this; } // Guard clause

    delete[] sequence;
    delete[] originalSequence;

    copy(src);
    return *this;
}


// Copy Constructor
ArithSeq::ArithSeq(const ArithSeq& src) {
    copy(src);
}

/// MOVE SEMANTICS (&&)
// Move Assignment Operator
ArithSeq::ArithSeq(ArithSeq&& src) {
    a1 = src.a1;
    dst = src.dst;
    n = src.n;
    maxOperations = src.maxOperations;
    sequence = src.sequence;
    originalSequence = src.originalSequence;
    operations = src.operations;

    src.a1 = 0;
    src.dst = 0;
    src.n = 0;
    src.maxOperations = 0;
    src.sequence = 0;
    src.originalSequence = 0;
    src.operations = 0;
}

// Move Constructor
ArithSeq &ArithSeq::operator=(ArithSeq&& src) {
    swap(a1, src.a1);
    swap(dst, src.dst);
    swap(n, src.n);
    swap(maxOperations, src.maxOperations);
    swap(sequence, src.sequence);
    swap(originalSequence, src.originalSequence);
    swap(operations, src.operations);

    return *this;
}

// Operations from P1
void ArithSeq::exceedsMaxOperations() {

	if (operations >= maxOperations) {
		throw invalid_argument("Exceeded max operations");
	}

	operations++;
}

int* ArithSeq::getSequence() {
    if (n == 0) {
        throw invalid_argument("Sequence is empty");
    }

    return sequence;
}

int ArithSeq::getKthValue(int k) {
    if (k < 0 || k >= n) {
        throw invalid_argument("K must be between 0 and sequence length");
    }

    exceedsMaxOperations();
    return getSequence()[k];
}

int ArithSeq::divisibleBy(int divisor) {
    if (divisor == 0)
    {
        throw invalid_argument("Divisor must not equal 0");
    }

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if ((sequence[i] % divisor) == 0)
        {
            count++;
        }
    }

    exceedsMaxOperations();
    return count;
}

void ArithSeq::modifySequence(int p, int q) {
    if (p < 0 || p >= n) {
        throw invalid_argument("p must be between 0 and sequence length");
    }

    if (q == 0) return; // ignore no change

    for (int i = p; i < n; i += (p == 0 ? 1 : q)) { // user can change sequence from 0
        sequence[i] += q;
    }

    exceedsMaxOperations();
}

void ArithSeq::reset() {
    for (int i = 0; i < n; i++) {
        sequence[i] = originalSequence[i];
    }

    operations = 0;
}

// public query regarding state
bool ArithSeq::canPerformMoreOperations() {
  return operations < maxOperations;
}