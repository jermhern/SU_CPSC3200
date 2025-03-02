//
// Created by Jeremy on 1/17/25.
//

/*
    Class Invariants:
    1.  Setting the maximum number of operations for Arith Seq must be at least 30,
        which will be set automatically within the constructor if a valid value is not given.
        A public query method is available to veridy that an object can perform an operation without
        throwing an exception.
    2. The length of the ArithSeq must always be greater than 0. The constructor will
        throw an error if an invalid length value (0 => n) is given.
    3. A valid difference for the construction of the object, and for the modify method, This prevents
        an invalid sequence to form, or no changes to be made.
    4. The original sequence value is used to keep track of the sequence before any operations can be made.
        This is required in order to return the sequence to its original state after Reset().
    5. In order to get the Kth value from an ArithSeq object the value k that is passed into the method must
       be larger than 0 and less than the sequence length, or an invalid argument exception will be thrown.
    6. In order to return the integer of values divisible by an integer, divisor parameter into the method must
       not equal 0, or divide by zero exception will be thrown.
	7. Overloaded Operators
* 	- >> and << will not be overloaded as operators +, += have been provided to stream data into thre desired object, and
	  due to the simplicity of the object, the client can use public methods .getSize() provided to print out the data
* 	- The +, += operators will work with other ArithSeq objects due to their complexity. Additionally, these operators
	  may be used with integers to increase each value in the sequence by the integer that has been passed in.
	  With this being said, addition is fully supported within the ArithSeq class.
 *  - The post/pre-fix operators ++ and -- will increment or decrement every value, in every ArithSeq object, by 1
* 	- Equality operators ==/!= have been provided and return a boolean regarding the equality of the ArithSeq Objects
* 	- the [] accessor has been overloaded which provides a way to return a integer to the valid index provided
*/

#include "ArithSeq.h"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <memory>

using namespace std;

// Constructor
ArithSeq::ArithSeq(int firstTerm, int difference, int sequenceLength, int maxOp): sequence(new int[sequenceLength]),
                                                                                  originalSequence(new int[sequenceLength])
{
    if (sequenceLength <= 0)
        throw invalid_argument("Sequence length must be greater than or equal to 0");

    if (maxOp < 0)
        throw invalid_argument("Max operations must be greater than 0");

    if (difference <= 0)
        throw invalid_argument("Difference must be greater than 0");

    // validated inputs, set fields
    a1 = firstTerm;
    dst = difference;
    n = sequenceLength;
    maxOperations = maxOp;

    // calculate each term of the sequence & create copy
    for (int i = 0; i < n; i++) {
      	sequence[i] = a1 + i * dst;
        originalSequence[i] = sequence[i];
    }

    operations = 0;
}

// PRECONDITION: destructor is no longer needed as dynamic memory is managed by smart pointers
// ArithSeq::~ArithSeq() {}

// Private utility function for copy
void ArithSeq::copy(const ArithSeq& src) {
    a1 = src.a1;
    dst = src.dst;

    n = src.n;
    maxOperations = src.maxOperations;
    operations = 0; // new objects will be set to 0

    sequence = shared_ptr<int[]>(new int[n]);
    for (int i = 0; i < n; i++) {
        sequence[i] = src.sequence[i];
    }

    originalSequence = shared_ptr<int[]>(new int[n]);
    for (int i = 0; i < n; i++) {
        originalSequence[i] = src.originalSequence[i];
    }
}

// Overloaded Operators
// PRECONDIITON: A valid arith seq object is given to be added to every value in the current sequence,
//				 otherwise an error will be thrown
// POSTCONDITION: All values within the ArithSeq object will be added to to the src object passed in. The opertion will
//				  only iterate to the lowest array size that is being altered in the operation.
ArithSeq ArithSeq::operator+(const ArithSeq& src) {

  	if (src.n == 0) { throw invalid_argument("Adding error: Please provide a valid ArithSeq"); }

    ArithSeq temp(src);
	temp += src; // reuse exisiting operator +=
    return temp;
}

// PRECONDIITON: A valid integer is given to increase every value in the sequence by num, otherwise an error will be thrown
// POSTCONDITION: All values within the ArithSeq object will be added to to the integer passed in.
ArithSeq ArithSeq::operator+(int num) {

  	if (num <= 0) { throw invalid_argument("Adding error: Please provide values larger than 0"); }

    ArithSeq temp(*this);
    temp += num; // reuse exisiting operator +=
    return temp;
}

// PRECONDIITON: A valid arith seq object is given, otherwise an error will be thrown
// POSTCONDITION: All values within the ArithSeq object will be added the ArithSeq values passed in.
ArithSeq& ArithSeq::operator+=(const ArithSeq& src) {

  	if (src.n == 0) { throw invalid_argument("Adding error: Please provide a valid ArithSeq"); }

    int min_index = (n < src.n) ? n : src.n; // Code from OperatorOverload PPTX: Dr. Dingle

    for (int i = 0; i < min_index; i++) {
    	sequence[i] += src.sequence[i];
    }

    return *this;
}

// PRECONDIITON: A valid integer is given, otherwise an error will be thrown
// POSTCONDITION: All values within the ArithSeq object will be added to to the integer passed in.
ArithSeq& ArithSeq::operator+=(int num) {

  	if (num <= 0) { throw invalid_argument("Adding error: Please provide values larger than 0"); }

    for (int i = 0; i < n; i++) {
    	sequence[i] += num;
    }

    return *this;
}

// PRECONDIITON: A valid arith seq object is given.
// POSTCONDITION: All values within the ArithSeq object will be made equal to the src object passed in
ArithSeq &ArithSeq::operator=(const ArithSeq& src) {
    if (this == &src) { return *this; } // Guard clause

    copy(src);
    return *this;
}

// PRECONDITION: Both sequences should have the same values and length to return true
bool ArithSeq::operator==(const ArithSeq& src) {
  if (n != src.n) { return false; }

  for (int i = 0; i < n; i++) {
    if (sequence[i] != src.sequence[i])
      return false;
  }
  return true;
}

// PRECONDITION: Both sequences should not have the same values and length to return true
bool ArithSeq::operator!=(const ArithSeq& src) {
	return !(*this == src); // negate == operation
}

// PRECONDIITON: A valid arith seq object is given. For pre-increment all values of the object will be incremented by 1
// POSTCONDITION: All values within the ArithSeq object will be incremented by 1
void ArithSeq::operator++() {
  for (int i = 0; i < n; i++) {
    sequence[i]++;
  }
}

// PRECONDIITON: A valid arith seq object is given. For post-increment all values of the object will be incremented by 1
// POSTCONDITION: All values within the ArithSeq object will be incremented by 1
void ArithSeq::operator++(int) {
  for (int i = 0; i < n; i++) {
    ++sequence[i];
  }
}

// PRECONDIITON: A valid arith seq object is given. For pre-decrement all values of the object will be decremented by 1
// POSTCONDITION: All values within the ArithSeq object will be decremented by 1
void ArithSeq::operator--() {
  for (int i = 0; i < n; i++) {
    sequence[i]--;
  }
}

// PRECONDIITON: A valid arith seq object is given. For post-decrement all values of the object will be decremented by 1
// POSTCONDITION: All values within the ArithSeq object will be decremented by 1
void ArithSeq::operator--(int) {
  for (int i = 0; i < n; i++) {
    --sequence[i];
  }
}

// PRECONDIITON: A valid arith seq object is given with a valid index passed into the method. If an invalid index is given,
//				 an exception will be thrown to the client
// POSTCONDITION: The [] accessor will return an integer of the value at the index of arithSeq
int ArithSeq::operator[](int index) {
  if (index > n || index < 0) { throw invalid_argument("ArithSeq index is out of bounds!"); }
  return sequence[index];
}

// Copy Constructor
ArithSeq::ArithSeq(const ArithSeq& src) {
    copy(src);
}

/// MOVE SEMANTICS (&&)
// Move Assignment Operator
ArithSeq::ArithSeq(ArithSeq&& src) {
    a1 = src.a1;
    dst = src.dst;
    n = src.n;
    maxOperations = src.maxOperations;
    operations = src.operations;

    originalSequence = std::move(src.originalSequence);
    sequence = std::move(src.sequence);

    src.a1 = 0;
    src.dst = 0;
    src.n = 0;
    src.maxOperations = 0;
    src.sequence = nullptr;
    src.originalSequence = nullptr;
    src.operations = 0;
}

// Move Constructor
ArithSeq &ArithSeq::operator=(ArithSeq&& src) {
  if (this != &src) { // guard
    swap(a1, src.a1);
    swap(dst, src.dst);
    swap(n, src.n);

    swap(maxOperations, src.maxOperations);
    swap(sequence, src.sequence);

    swap(originalSequence, src.originalSequence);
    swap(operations, src.operations);
  }
  return *this;
}

// Operations from P1
void ArithSeq::exceedsMaxOperations() {

	if (operations >= maxOperations) {
		throw invalid_argument("Exceeded max operations");
	}

	operations++;
}

shared_ptr<int[]> ArithSeq::getSequence() {
    if (n == 0) {
        throw invalid_argument("Sequence is empty");
    }

	return sequence;
}

int ArithSeq::getKthValue(int k) {
    if (k < 0 || k >= n) {
        throw invalid_argument("K must be between 0 and sequence length");
    }

    exceedsMaxOperations();
    return sequence[k];
}

int ArithSeq::divisibleBy(int divisor) {
    if (divisor == 0)
    {
        throw invalid_argument("Divisor must not equal 0");
    }

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if ((sequence[i] % divisor) == 0)
        {
            count++;
        }
    }

    exceedsMaxOperations();
    return count;
}

int ArithSeq::getSize() {
  return n;
}

void ArithSeq::modifySequence(int p, int q) {
    if (p < 0 || p >= n) {
        throw invalid_argument("p must be between 0 and sequence length");
    }

    if (q == 0) return; // ignore no change

    for (int i = p; i < n; i ++) { // user can change sequence from 0
        sequence[i] += q;
    }

    exceedsMaxOperations();
}

void ArithSeq::reset() {
    for (int i = 0; i < n; i++) {
        sequence[i] = originalSequence[i];
    }

    operations = 0;
}

// public query regarding state
bool ArithSeq::canPerformMoreOperations() {
  return operations < maxOperations;
}

/*
 * Implementation Invariant:
 *  1. The maxOperations variable must always be 30 >=. If this is not provided within the constructor it will default.
 *  2. The length of the sequence, n, must always be greater than 0.
 *  3. The difference between terms, dst, must always be greater than 0.
 *  4. The originalSequence array will always be equal to the initial state of sequence when it is constructed.
 *  5. The sequence array will always have the same length as 'n', and reflect values from the initial sequence formula.
 *     Deviations to the original sequence formula will be performed by the ModifySequence method.
 *   6. The getKthValue method parameter must recieve a value larger than 0 and less than the sequence length.
 *   7. The divisibleBy method parameter must not equal 0
* 	 8. "In C++17 it is recommended that the form array form std::shared_ptr<T[]> should be used rather than
 * 		constructing a std::shared_ptr<T> from a std::unique_ptr<T[]> in C++11 and C++14" - cppreference
* 	9. ArithSeq fully supports ArithSeq and integer addition through +, += operators
* 	10. ArithSeq supports ==/!= operators, post/pre-fix operators for incrementation and subtraction (++/--),
 * 		the [] accessor which will return an integer belonging to the ArithSeq object
 */