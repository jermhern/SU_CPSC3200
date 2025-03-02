//
// Created by Jeremy on 1/21/25.
// cpp file for AsymPattern Implementation
//

#include "AsymPattern.h"
#include "ArithSeq.h"

#include <iostream>
#include <stdexcept>

/*
* Class invariants:
* 1. Capacity Management
*    - The MAX_CAPACITY constant has been enforced within the AsymPattern constructor to prevent allocation requests
*      exceeding 10 positions for ArithSeq objects.
*    - The array size is set to 10 if no size is provided.
*    - If a size greater than 10 is provided, an invalid_argument exception will be thrown
* 2. AsymPattern Constructor Requirements
 *   - Requires a valid array of ArithSeq objects stored within an array.
*    - If the array is empty, or invalid, an invalid_argument excetion will be thrown.
* 3. addArithSeq() allows to write to the initial array that was passed into the object with addArithSeq. If the method
*    is called and:
*     1. The AsymPattern object is at capacity
*     2. An invalid key is passed into the method
*   an exception will be thrown for invalid writing.
* 4. setArithSeq() allows to write to patterns within the AsymPattern object. If the key passed into the method is invalid
*    an exception will be thrown due to an invalid request.
* 5. reset() allows to reset all patterns within the AsymPattern object to their original state. If the key passed into
 *   the method is invalid an exception will be thrown due to an invalid request.
*/

AsymPattern::AsymPattern(ArithSeq* sequences, int size) {

    if (size > MAX_CAPACITY) {
       throw invalid_argument("Size given exceeds max capacity");
    }

    if (sequences == nullptr) {
        throw invalid_argument("Null ArithSeq Dependency recieved");
    }

    // inject via constructor
    this->size_ = size;
    this->sequences_ = new ArithSeq* [size_];

    for (int i = 0; i < size_; i++) {
      // AsymPattern will not own objects
      sequences_[i] = &sequences[i];
    }
}

AsymPattern::~AsymPattern() {
  delete[] sequences_;
}

// Private utility function for copy
void AsymPattern::copy(const AsymPattern& src) {
  size_ = src.size_;

  sequences_ = new ArithSeq* [size_];
  for (int i = 0; i < size_; i++) {
    sequences_[i] = src.sequences_[i];
  }
}

// Overloaded Assignment Operator
AsymPattern &AsymPattern::operator=(const AsymPattern& src) {
  if (this == &src) { return *this; } // guard clause

  delete[] sequences_;
  copy(src);

  return *this;
}

// Copy Constructor
AsymPattern::AsymPattern(const AsymPattern& src) {
  copy(src);
}

/// MOVE SEMANTICS (&&)
// Move Assignment Operator
AsymPattern::AsymPattern(AsymPattern&& src) {
    size_ = src.size_;
    sequences_ = src.sequences_;

    src.size_ = 0;
    src.sequences_ = 0;
}

// Move Constructor
AsymPattern &AsymPattern::operator=(AsymPattern&& src) {

  swap(size_, src.size_);
  swap(sequences_, src.sequences_);

  return *this;
}

bool AsymPattern::seqExists(int key) {
    if (key >= 0 && key < size_) { return true; }
    return false;
}

bool AsymPattern::atCapacity() {
  return size_ <= MAX_CAPACITY;
}

void AsymPattern::addArithSeq(int key, ArithSeq& seq) {
    if (atCapacity() && key >= MAX_CAPACITY-1) {
        throw invalid_argument("Adding sequence out of bounds not allowed. Please overwrite existing memory.");
    }

    sequences_[key] = &seq;
}

void AsymPattern::setArithSeq(int p, int q, int key) {

    if (!seqExists(key)) {
    	throw invalid_argument("Set Error: Invalid key for accessing ArithSeq");
    }

    sequences_[key]->modifySequence(p,q);
}

void AsymPattern::resetSeq(int key) {

    if (!seqExists(key)) {
        throw invalid_argument("Reset Error: Invalid key for accessing ArithSeq");
    }

    sequences_[key]->reset();
}

/*
* Implementation invariants:
* 1. MAX_CAPACITY limits the array size to 10 for efficiency and to prevent excessive heap usage. The constructor
 *   will enforce this and will throw an exception if invalid size passed.
* 2. Public methods for AsymPattern (resetSeq, setArithSeq, addArithSeq, seqExists) require a valid key to access the
 *   internal pattern, ArithSeq of the AsymPattern object. If an invalid key is provided, an exception will be thrown.
* 3. Reset() restores a valid key sequences to its original state.
*
*/
