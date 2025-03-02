//
// Updated by Jeremy on 3/2/25.
// Header file in C++ for ArithSeq
//

#ifndef ARITHSEQ_H
#define ARITHSEQ_H

#include <memory>
using namespace std;

class ArithSeq {
public:
    ArithSeq() = default;
    ArithSeq(int firstTerm, int difference, int sequenceLength, int maxOp = 30);
    ArithSeq(const ArithSeq &); // Copy Constructor
    ArithSeq(ArithSeq &&src);

    ArithSeq &operator=(const ArithSeq &); // Overloaded Assignment Operator
    ArithSeq &operator=(ArithSeq &&);

    virtual ~ArithSeq() = default;
    shared_ptr<int[]> getSequence();

    virtual int getKthValue(int k);
    virtual int divisibleBy(int divisor);
    int getSize();
    virtual void modifySequence(int p, int q);
    virtual void reset();
    bool canPerformMoreOperations(); // public query regarding state

    // operator overloading
    ArithSeq operator+(const ArithSeq&);
    ArithSeq& operator+=(const ArithSeq&);

    ArithSeq operator+(int);
    ArithSeq& operator+=(int);

    bool operator==(const ArithSeq&);
    bool operator!=(const ArithSeq&);
    virtual void operator++();
    virtual void operator++(int);
    virtual void operator--();
    virtual void operator--(int);
    int operator[](int);

protected:
    void exceedsMaxOperations();
    void copy(const ArithSeq &); // Private utility function for copy

    shared_ptr<int[]> sequence;
    shared_ptr<int[]> originalSequence;

    int operations;
    int maxOperations;
    int a1;
    int dst;
    int n;
};

#endif //ARITHSEQ_H
