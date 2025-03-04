//
// Created by Jeremy on 3/2/25.
// Driver file in C++ for P4
//

#include "ArithSeq.h"
#include "AsymPattern.h"
#include "DurableSeq.h"
#include <iostream>

using namespace std;

// Global test objects for testing
// Initialize individual ArithSeq Objects with various sequences
ArithSeq aSeq(1,1,10,30);
ArithSeq aSeq1(2,2,10,20);
ArithSeq aSeq2(3,3,10,10);
ArithSeq aSeq3(5,5,15,40);
ArithSeq aSeq4(9,1,20,30);
ArithSeq aSeq5(3,2,10,20);
ArithSeq aSeq6(10,3,10,10);
ArithSeq aSeq7(100,5,15,40);

// Initialize an array aof ArithSeq objects
ArithSeq aSeqs[4] = {aSeq, aSeq1, aSeq2, aSeq3};
ArithSeq aSeqs1[2] = {aSeq4, aSeq5};
ArithSeq aSeqs2[5] = {aSeq, aSeq5, aSeq7, aSeq2, aSeq3};

// Initialize various AsymPattern objects with varying sizes and sequences
AsymPattern aPattern(aSeqs, 4);
AsymPattern aPattern1(aSeqs1, 2);
AsymPattern aPattern2(aSeqs2, 5);

// Initialize various DurableSeq objects with varying sizes and sequences
DurableSeq dPattern(aSeqs, 4, "dPatternOne");
DurableSeq dPattern1(aSeqs1, 2, "dPatternTwo");
DurableSeq dPattern2(aSeqs2, 5); // Default name used

void testArithSeqOperators() {
    cout << "===== Testing ArithSeq Operators =====" << endl;

    // ==
    cout << "===== (==) Equality Testing =====" << endl;
    cout << "ArithSeq A: ";
    for (int i = 0; i < aSeq.getSize(); i++) {
        cout << aSeq[i] << " ";
    }

    cout << endl;

    cout << "ArithSeq B: ";
    for (int i = 0; i < aSeq1.getSize(); i++) {
        cout << aSeq1[i] << " ";
    }

    cout << endl << "A == B " << (aSeq == aSeq1 ? "True" : "False") << endl;
    cout << "A == A " << (aSeq == aSeq ? "True" : "False") << endl;
    cout << "B == B " << (aSeq1 == aSeq1 ? "True" : "False") << endl;
    cout << endl << "==============================================" << endl;

    // !=
    cout << "===== (!=) Inequality Testing =====" << endl;
    cout << "ArithSeq A: ";
    for (int i = 0; i < aSeq5.getSize(); i++) {
        cout << aSeq5[i] << " ";
    }

    cout << endl;

    cout << "ArithSeq B: ";
    for (int i = 0; i < aSeq7.getSize(); i++) {
        cout << aSeq7[i] << " ";
    }

    cout << endl << "A != B " << (aSeq5 != aSeq7 ? "True" : "False") << endl;
    cout << "A != A " << (aSeq5 != aSeq5 ? "True" : "False") << endl;
    cout << "B != B " << (aSeq7 != aSeq7 ? "True" : "False") << endl;

    cout << endl << "==============================================" << endl;

    // Pre-Post fix increment (++)
    cout << "===== (++) Pre-Post fix increment Testing =====" << endl;
    cout << "ArithSeq A before pre-fix increment: ";
    for (int i = 0; i < aSeq.getSize(); i++) {
        cout << aSeq[i] << " ";
    }

    ++aSeq;
    cout << endl;

    cout << "ArithSeq A after pre-fix increment: ";
    for (int i = 0; i < aSeq.getSize(); i++) {
        cout << aSeq[i] << " ";
    }

    cout << endl;

    cout << "ArithSeq B before post-fix increment: ";
    for (int i = 0; i < aSeq4.getSize(); i++) {
        cout << aSeq4[i] << " ";
    }

    aSeq4++;
    cout<< endl;

    cout << "ArithSeq B after post-fix increment: ";
    for (int i = 0; i < aSeq4.getSize(); i++) {
        cout << aSeq4[i] << " ";
    }

    cout << endl << "==============================================" << endl;

    // Pre-Post fix decrement (--)
    cout << "===== (--) Pre-Post fix decrement Testing =====" << endl;
    cout << "ArithSeq A before pre-fix decrement: ";
    for (int i = 0; i < aSeq.getSize(); i++) {
        cout << aSeq[i] << " ";
    }

    --aSeq;
    cout << endl;

    cout << "ArithSeq A after pre-fix decrement: ";
    for (int i = 0; i < aSeq.getSize(); i++) {
        cout << aSeq[i] << " ";
    }

    cout << endl;

    cout << "ArithSeq B before post-fix decrement: ";
    for (int i = 0; i < aSeq4.getSize(); i++) {
        cout << aSeq4[i] << " ";
    }

    aSeq4--;
    cout<< endl;

    cout << "ArithSeq B after post-fix decrement: ";
    for (int i = 0; i < aSeq4.getSize(); i++) {
        cout << aSeq4[i] << " ";
    }

    cout << endl << "==============================================" << endl;

    // Access [] operator
    cout << "===== ([]) Access [] operator Testing =====" << endl;
    cout << "aSeq1[3]: " << aSeq1[3] << endl;
    cout << "aSeq7[4]: " << aSeq7[4] << endl;
    cout << "aSeq5[5]: " << aSeq5[5] << endl;
    cout << "aSeq[6]: " << aSeq[6] << endl;
    cout << "aSeq[-4]: " << "Will throw OOB Error" << endl;
    cout << "aSeq4[6]: " << aSeq4[6] << endl;


    cout << endl << "==============================================" << endl;

    // + and += operator
    cout << "===== (+ & +=) Addition operator Testing =====" << endl;
    cout << "Adding ArithSeq objects to eachother: " << endl;
    cout << "ArithSeq A: ";
    for (int i = 0; i < aSeq.getSize(); i++) {
        cout << aSeq[i] << " ";
    }

    cout << endl;

    cout << "ArithSeq B: ";
    for (int i = 0; i < aSeq.getSize(); i++) {
        cout << aSeq[i] << " ";
    }

    cout << endl;

    cout << "aSeq1 + aSeq = ";
    ArithSeq temp(aSeq1 + aSeq);
    for (int i = 0; i < temp.getSize(); i++) {
        cout << temp[i] << " ";
    }

    cout << endl << endl;

    cout << "ArithSeq A: ";
    for (int i = 0; i < aSeq2.getSize(); i++) {
        cout << aSeq2[i] << " ";
    }

    cout << endl;

    cout << "ArithSeq B: ";
    for (int i = 0; i < aSeq3.getSize(); i++) {
        cout << aSeq3[i] << " ";
    }

    cout << endl;

    cout << "aSeq2+=aSeq3; Out: ";
    aSeq2+=aSeq3;
    for (int i = 0; i < aSeq2.getSize(); i++) {
        cout << aSeq2[i] << " ";
    }

    cout << endl << endl;

    cout << "Adding integers to ArithSeq objects: " << endl;
    cout << "ArithSeq A: ";
    for (int i = 0; i < aSeq2.getSize(); i++) {
        cout << aSeq2[i] << " ";
    }

    cout << endl;

    cout << "aSeq2 + 5: ";
    aSeq2 = aSeq2 + 5;
    for (int i = 0; i < aSeq2.getSize(); i++) {
        cout << aSeq2[i] << " ";
    }

    cout << endl << endl;

    cout << "ArithSeq A: ";
    for (int i = 0; i < aSeq.getSize(); i++) {
        cout << aSeq[i] << " ";
    }

    cout << endl;

    cout << "aSeq += 100: ";
    aSeq += 100;
    for (int i = 0; i < aSeq.getSize(); i++) {
        cout << aSeq[i] << " ";
    }

    cout << endl << "==============================================" << endl;
}

void testAsymOperators() {
    cout << "===== Testing AsymPattern Operators =====" << endl;

    cout << "===== (==) Equality Testing =====" << endl;

    cout << "AsymPattern A: " << endl << aPattern << endl;
    cout << "AsymPattern B: " << endl << aPattern1 << endl;

    cout << "A == B " << (aPattern == aPattern1 ? "True" : "False") << endl;
    cout << "A == A " << (aPattern == aPattern ? "True" : "False") << endl;
    cout << "B == B " << (aPattern1 == aPattern1 ? "True" : "False") << endl;
    cout << endl << "==============================================" << endl;

    cout << "===== (!=) Inequality Testing =====" << endl;

    cout << "AsymPattern A: " << endl << aPattern1 << endl;
    cout << "AsymPattern B: " << endl << aPattern2 << endl;

    cout << "A != B " << (aPattern1 != aPattern2 ? "True" : "False") << endl;
    cout << "A != A " << (aPattern1 != aPattern1 ? "True" : "False") << endl;
    cout << "B != B " << (aPattern2 != aPattern2 ? "True" : "False") << endl;
    cout << endl << "==============================================" << endl;

    cout << "===== (++) Post-Pre Increment Testing =====" << endl;
    cout << "AsymPattern A Before Pre-Increment: " << endl << aPattern1 << endl;
    ++aPattern1;
    cout << "AsymPattern A After Pre-Increment: " << endl << aPattern1 << endl;

    cout << "AsymPattern A Before Post-Increment: " << endl << aPattern2 << endl;
    aPattern2++;
    cout << "AsymPattern A After Post-Increment: " << endl << aPattern2;
    cout << endl << "==============================================" << endl;

    cout << "===== (--) Post-Pre Decrement Testing =====" << endl;
    cout << "AsymPattern A Before Pre-Decrement: " << endl << aPattern << endl;
    --aPattern;
    cout << "AsymPattern A After Pre-Decrement: " << endl << aPattern << endl;

    cout << "AsymPattern A Before Post-Decrement: " << endl << aPattern1 << endl;
    aPattern1--;
    cout << "AsymPattern A After Post-Decrement: " << endl << aPattern1;
    cout << endl << "==============================================" << endl;

    cout << "===== ([]) Accessor Testing =====" << endl;

    cout << "aPattern1: " << endl << aPattern;
    cout << "ArithSeq temp(aPattern[1]): " << endl;
    ArithSeq temp(aPattern[1]);
    cout << "temp[1]: ";
    for (int i = 0; i < aSeq1.getSize(); i++) {
        cout << temp[i] << " ";
    }

    cout << endl << "==============================================" << endl;

    cout << "===== (<<) Ostream Operator Testing =====" << endl;

    cout << "aPattern <<:" << endl << aPattern;
    cout << "aPattern1 <<:" << endl << aPattern1;
    cout << "aPattern2 <<:" << endl << aPattern2;

    cout << "==============================================" << endl;
}

void testDurableOperators() {
    cout << endl << "===== Testing DurableSeq Operators =====" << endl;

    cout << "===== (==) Equality Testing =====" << endl;
    cout << "DurableSeq A: " << endl << dPattern;
    cout << "DurableSeq B: " << endl << dPattern1;

    cout << "A == B " << (dPattern == dPattern1 ? "True" : "False") << endl;
    cout << "A == A " << (dPattern == dPattern ? "True" : "False") << endl;
    cout << "B == B " << (dPattern1 == dPattern1 ? "True" : "False") << endl;
    cout << endl << "==============================================" << endl;

    cout << "===== (!=) Inequality Testing =====" << endl;
    cout << "DurableSeq A: " << endl << dPattern2;
    cout << "DurableSeq B: " << endl << dPattern;

    cout << "A != B " << (dPattern2 != dPattern ? "True" : "False") << endl;
    cout << "A != A " << (dPattern2 != dPattern2 ? "True" : "False") << endl;
    cout << "B != B " << (dPattern != dPattern ? "True" : "False") << endl;
    cout << endl << "==============================================" << endl;

    cout << "===== (++) Post-Pre Increment Testing =====" << endl;
    cout << "AsymPattern A Before Pre-Increment: " << endl << dPattern << endl;
    ++dPattern;
    cout << "AsymPattern A After Pre-Increment: " << endl << dPattern << endl;

    cout << "AsymPattern A Before Post-Increment: " << endl << dPattern1 << endl;
    dPattern1++;
    cout << "AsymPattern A After Post-Increment: " << endl << dPattern1;
    cout << endl << "==============================================" << endl;

    cout << "===== (--) Post-Pre Decrement Testing =====" << endl;
    cout << "AsymPattern A Before Pre-Decrement: " << endl << dPattern2 << endl;
    --dPattern2;
    cout << "AsymPattern A After Pre-Decrement: " << endl << dPattern2 << endl;

    cout << "AsymPattern A Before Post-Decrement: " << endl << dPattern << endl;
    dPattern--;
    cout << "AsymPattern A After Post-Decrement: " << endl << dPattern;
    cout << endl << "==============================================" << endl;

    cout << "===== ([]) Accessor Testing =====" << endl;
    cout << "dPattern1: " << endl << dPattern1;
    cout << "ArithSeq temp(dPattern[1]): " << endl;
    ArithSeq temp(dPattern[1]);
    cout << "temp[1]: ";
    for (int i = 0; i < aSeq1.getSize(); i++) {
        cout << temp[i] << " ";
    }
    cout << endl << "==============================================" << endl;

    cout << "===== (<<) Ostream Operator Testing =====" << endl;
    cout << "dPattern <<:" << endl << dPattern;
    cout << "dPattern1 <<:" << endl << dPattern1;
    cout << "dPattern2 <<:" << endl << dPattern2;
    cout << "==============================================" << endl;
}

void runTests() {
    testArithSeqOperators();
    testAsymOperators();
    testDurableOperators();
}

void exitTesting() {
    cout << "All tests completed successfully!" << endl;
}

int main() {
    runTests();
    exitTesting();

    return 0;
}