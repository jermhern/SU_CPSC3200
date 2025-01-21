//
// Created by Jeremy on 1/21/25.
// cpp file for AsymPattern Implementation
//

#include "AsymPattern.h"
#include "ArithSeq.h"

#include <map>
#include <iostream>
#include <stdexcept>


AsymPattern::AsymPattern(const map<int, ArithSeq> inject) {
  	// add logic to prevent overflow
	sequences = inject;
    originalSequences = inject;
}

AsymPattern::~AsymPattern() {}

// Private utility function for copy

// Overloaded Assignment Operator

// Copy Constructor

/// MOVE SEMANTICS (&&)
// Move Assignment Operator
// Move Constructor

bool AsymPattern::seqExists(int key) {
	return (sequences.find(key) != sequences.end());
}

bool AsymPattern::atCapacity() {
	return (sequences.size() < MAX_CAPACITY);
}

void AsymPattern::addArithSeq(int key, const ArithSeq& seq) {

  	if (seqExists(key)) {
    	throw invalid_argument("Invalid key - cannot overwrite values with exisiting keys");
  	}

    if (!atCapacity()) {
     	sequences.insert({key, seq});
    }
}

ArithSeq AsymPattern::getArithSeq(int key) {

  if (seqExists(key)) {
    throw invalid_argument("Invalid key for accessing ArithSeq");
  }

  return sequences.at(key);
}

void AsymPattern::removeArithSeq(int key) {
  if (seqExists(key)) {
    throw invalid_argument("Invalid key for removing ArithSeq");
  }

  sequences.erase(key);
}

void AsymPattern::reset() {
  sequences = originalSequences;
}