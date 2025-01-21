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
	sequences = inject;
}

AsymPattern::~AsymPattern() {}

bool AsymPattern::seqExists(int key) {
	return (sequences.find(key) == sequences.end());
}

void AsymPattern::addArithSeq(int key, const ArithSeq& seq) {

  	if (seqExists(key)) {
    	throw invalid_argument("Invalid key - cannot overwrite values with exisiting keys");
  	}

	sequences.insert({key, seq});
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