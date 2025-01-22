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

// Overloaded Assignment Operator

// Copy Constructor

/// MOVE SEMANTICS (&&)
// Move Assignment Operator
// Move Constructor

bool AsymPattern::seqExists(int key) {
  	if (key >= 0 && key < size_) {
    	return true;
    }
	return true;
}

bool AsymPattern::atCapacity() {
  return size_ <= MAX_CAPACITY;
}

void AsymPattern::setArithSeq(int p, int q, int key) {

  	if (seqExists(key)) {
    	throw invalid_argument("Invalid key - cannot overwrite values with exisiting keys");
  	}

    sequences_[key]->modifySequence(p,q);
}

ArithSeq* AsymPattern::getArithSeq(int key) {

  if (seqExists(key)) {
    throw invalid_argument("Invalid key for accessing ArithSeq");
  }

  return sequences_[key];
}


void AsymPattern::resetSeq(int key) {
  sequences_[key]->reset();
}