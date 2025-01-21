#include "ArithSeq.h"
#include "AsymPattern.h"
#include <iostream>
#include <map>

using namespace std;

int main() {

  ArithSeq aSeq(1, 2, 5, 30);
  ArithSeq bSeq(1, 1, 5, 30);
  ArithSeq cSeq(1, 2, 10, 30);

  const map<int, ArithSeq> INJECT = { {1, aSeq}, {2, bSeq}, {3, cSeq} };
  AsymPattern collection(INJECT);

  collection.addArithSeq(1, ArithSeq(1, 10, 10, 30));

  cout << collection.getArithSeq(1).getKthValue(4);

  return 0;
}