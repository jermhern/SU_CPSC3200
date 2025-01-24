//
// Created by Jeremy on 1/21/25.
// cpp file for AsymPattern Implementation
//

#include "AsymPattern.h"
#include "ArithSeq.h"

#include <map>
#include <iostream>
#include <stdexcept>

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
  	if (key >= 0 && key < size_) {
    	return true;
    }
	return false;
}

bool AsymPattern::atCapacity() {
  return size_ <= MAX_CAPACITY;
}

void AsymPattern::setArithSeq(int p, int q, int key) {

  	if (!seqExists(key)) {
    	throw invalid_argument("Invalid key for accessing ArithSeq");
  	}

    sequences_[key]->modifySequence(p,q);
}

ArithSeq* AsymPattern::getArithSeq(int key) {

  if (!seqExists(key)) {
    throw invalid_argument("Invalid key for accessing ArithSeq");
  }

  return sequences_[key];
}

void AsymPattern::resetSeq(int key) {
  sequences_[key]->reset();
}