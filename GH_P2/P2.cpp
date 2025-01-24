#include "ArithSeq.h"
#include "AsymPattern.h"
#include <iostream>
#include <map>

using namespace std;

int main() {

  ArithSeq aSeq(1, 2, 5, 30);
  ArithSeq bSeq(2, 1, 5, 30);
  ArithSeq cSeq(3, 2, 10, 30);
  ArithSeq dSeq(3,1,1,20);

  ArithSeq sequences[3] = {aSeq, bSeq, cSeq};

  AsymPattern pattern(sequences, 3);
  pattern.resetSeq(0);
  pattern.getArithSeq(1)->testPrint();
  pattern.setArithSeq(0, 10, 1);
  pattern.getArithSeq(1)->testPrint();

  AsymPattern pattern2(pattern);
  pattern2.getArithSeq(1);
  pattern.addArithSeq(4, dSeq);

  return 0;
}