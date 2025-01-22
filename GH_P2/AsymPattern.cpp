//
// Created by Jeremy on 1/21/25.
// cpp file for AsymPattern Implementation
//

#include "AsymPattern.h"
#include "ArithSeq.h"

#include <map>
#include <iostream>
#include <stdexcept>


AsymPattern::AsymPattern(ArithSeq* seq) {

}

AsymPattern::~AsymPattern() {}

// Private utility function for copy

// Overloaded Assignment Operator

// Copy Constructor

/// MOVE SEMANTICS (&&)
// Move Assignment Operator
// Move Constructor

bool AsymPattern::seqExists(int key) {
	return false;
}

bool AsymPattern::atCapacity() {
  return false;
}

void AsymPattern::addArithSeq(int key, const ArithSeq& seq) {

  	if (seqExists(key)) {
    	throw invalid_argument("Invalid key - cannot overwrite values with exisiting keys");
  	}
}

ArithSeq* AsymPattern::getArithSeq(int key) {

  if (seqExists(key)) {
    throw invalid_argument("Invalid key for accessing ArithSeq");
  }
}

void AsymPattern::removeArithSeq(int key) {
  if (seqExists(key)) {
    throw invalid_argument("Invalid key for removing ArithSeq");
  }
}

void AsymPattern::resetAllSeq() {}