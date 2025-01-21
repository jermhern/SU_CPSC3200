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

  return 0;
}