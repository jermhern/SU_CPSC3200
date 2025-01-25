#include "ArithSeq.h"
#include "AsymPattern.h"
#include <iostream>
#include <map>

using namespace std;

int main() {

  ArithSeq aSeq(1, 2, 5, 30);
  ArithSeq bSeq(2, 1, 5, 30);
  ArithSeq cSeq(3, 2, 10, 30);
  ArithSeq sequencesA[3] = {aSeq, bSeq, cSeq};

  ArithSeq eSeq(1, 3, 20, 10);
  ArithSeq fSeq(2, 2, 20, 10);
  ArithSeq gSeq(3, 1, 10, 30);
  ArithSeq sequencesB[3] = {eSeq, fSeq, gSeq};

  ArithSeq iSeq(1, 30, 50, 10);
  ArithSeq jSeq(1, 20, 30, 10);
  ArithSeq kSeq(1, 10, 15, 20);
  ArithSeq sequencesC[3] = {iSeq, jSeq, kSeq};

  AsymPattern patternA(sequencesA, 4);
  AsymPattern patternB(sequencesB, 3);
  AsymPattern patternC(sequencesC); // default size, 10, used

  // adding & modifying sequences
  ArithSeq seqToAdd(1,9,9,9);
  patternA.addArithSeq(4, seqToAdd);
  patternA.setArithSeq(1, 2, 1);

  // assignment operator
  patternB = patternA;
  patternB.resetSeq(1);

  // call by value
  AsymPattern patternD(patternA);

  patternC.setArithSeq(1,2,2);
  patternD = patternC;


  return 0;
}