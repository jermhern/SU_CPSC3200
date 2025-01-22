#include "ArithSeq.h"
#include "AsymPattern.h"
#include <iostream>
#include <map>

using namespace std;

int main() {

  ArithSeq aSeq(1, 2, 5, 30);
  ArithSeq bSeq(2, 1, 5, 30);
  ArithSeq cSeq(3, 2, 10, 30);

  ArithSeq sequences[3] = {aSeq, bSeq, cSeq};

  AsymPattern pattern(sequences, 3);
  pattern.resetSeq(0);
  pattern.getArithSeq(2);
  pattern.setArithSeq(1, 1, 1);

  return 0;
}