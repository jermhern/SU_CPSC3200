//
// Created by Jeremy on 1/17/25.
// Header file in C++ for ArithSeq
//

#ifndef ARITHSEQ_H
#define ARITHSEQ_H

class ArithSeq {
    public:
      ArithSeq(int firstTerm, int difference, int sequenceLength, int maxOp = 30);
      ArithSeq(const ArithSeq&); // Copy Constructor
      ArithSeq(ArithSeq&& src);
      ArithSeq& operator=(const ArithSeq&); // Overloaded Assignment Operator
      ArithSeq& operator=(ArithSeq&&);
      ~ArithSeq();

      int* getSequence();
      int getKthValue(int k);
      int divisibleBy(int divisor);
      void modifySequence(int p, int q);
      void reset();

    private:
      void exceedsMaxOperations();
      void copy(const ArithSeq&); // Private utility function for copy

      int* sequence;
      int* originalSequence;

      int operations;
      int maxOperations;
      int a1;
      int dst;
      int n;
};

#endif //ARITHSEQ_H
