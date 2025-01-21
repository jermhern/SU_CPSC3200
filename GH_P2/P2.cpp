#include "ArithSeq.h"
#include <iostream>

using namespace std;

int main() {

  ArithSeq as(1,2,10, 30);
  ArithSeq ab(as);
  const ArithSeq ac(1, 1, 10, 30);

  AsymPattern collection;

  for (int i = 0; i < 5; i++) {
    cout << as.getSequence()[i] << " ";
  }

  cout << endl;

  for (int i = 0; i < 5; i++) {
    cout << ab.getSequence()[i] << " ";
  }

  cout << endl;
  ab = ac;

  for (int i = 0; i < 10; i++) {
    cout << ab.getSequence()[i] << " ";
  }


  return 0;
}