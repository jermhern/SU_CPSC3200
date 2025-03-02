//
// Created by Jeremy on 3/2/25.
// Driver file in C++ for P4
//

#include "ArithSeq.h"
#include "AsymPattern.h"
#include "DurableSeq.h"
#include <iostream>

using namespace std;

int main() {

    ArithSeq aSeq(1, 1, 5, 30);
    ArithSeq bSeq(1, 1, 5, 30);
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

    return 0;
}