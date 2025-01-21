//
// Created by Jeremy on 1/17/25.
//

#include "ArithSeq.h"
#include <stdexcept>
#include <utility>

using namespace std;

// Constructor
ArithSeq::ArithSeq(int firstTerm, int difference, int sequenceLength, int maxOp) {

    if (sequenceLength <= 0)
    {
        throw invalid_argument("Sequence length must be greater than or equal to 0");
    }

    if (maxOp < 0)
    {
        throw invalid_argument("Max operations must be greater than 0");
    }

    if (difference <= 0)
    {
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
    operations = src.operations;

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

//// Move Constructor
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
