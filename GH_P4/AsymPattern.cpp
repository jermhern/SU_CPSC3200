//
// Updated by Jeremy on 3/2/25.
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
* 6. Overloaded Operators
* 	- >> will not be overloaded as operators +, += have been provided to stream data into thre desired object
* 	- the << operator provides a convenient way to print all of the ArithSeq objects that are present within the current
* 	  AsymPattern object with information to view index as well
* 	- The +, += operators will only work with other AsymPattern objects due to their complexity. Using these operators
* 	  will add together all sequences with each other up to the smallest index to prevent out of bounds exceptions.
 *  - The post/pre-fix operators ++ and -- will increment or decrement every value, for AsymPattern
 * 	  in every ArithSeq object, by 1
* 	- Equality operators ==/!= have been provided and return a boolean regarding the equality of the AsymPattern Objects
* 	- the [] accessor has been overloaded which provides a way to return a shared_ptr to the valid index provided
*/

// AsymPattern()
// PRECONDITIONS:
    // sequences is an ArithSeq object, it must contain sequences, and be within bound, or else an exception is thrown
// POST-CONDITIONS:
    // the AsymPattern object has been initialized with a valid ArithSeq array
    // size_ is set to object array length
    // sequences_ copies all sequences from array of ArithSeq objects
AsymPattern::AsymPattern(ArithSeq* sequences, int size): sequences_(), originalSequences_()
{

  	if (size <= 0) {
       throw invalid_argument("Invalid Size: Must be greater than 0");
  	}

    if (size > MAX_CAPACITY) {
       throw invalid_argument("Size given exceeds max capacity");
    }

    if (sequences == nullptr) {
        throw invalid_argument("Null ArithSeq Dependency recieved");
    }

    // inject via constructor
    size_ = size;
    originalSize_ = size;

    sequences_ = shared_ptr<ArithSeq[]>(new ArithSeq[size_]);
    originalSequences_ = shared_ptr<ArithSeq[]>(new ArithSeq[size_]);

    for (int i = 0; i < size_; i++) {
      // AsymPattern will not own objects
      sequences_[i] = sequences[i];
      originalSequences_[i] = sequences_[i];
    }
}

// PRECONDITION: destructor is no longer needed as dynamic memory is managed by smart pointers
AsymPattern::~AsymPattern() {}

// Private utility function for copy
// PRECONDITION: A valid AsymPattern object is given to the overloaded = operator
// POSTCONDITION: Utilzing the private utility copy function the current AsymPattern object will take data from src
//				  only if the two objects do not share the same address. The new AsymPattern object will be returned
void AsymPattern::copy(const AsymPattern& src) {
  size_ = src.size_;

  sequences_ = shared_ptr<ArithSeq[]>(new ArithSeq[size_]);
  originalSequences_ = shared_ptr<ArithSeq[]>(new ArithSeq[size_]);

  for (int i = 0; i < size_; i++) {
    sequences_[i] = src.sequences_[i];
    originalSequences_[i] = src.originalSequences_[i];
  }
}

// Overloaded Operators
// PRECONDITION: A valid AsymPattern object is given to the overloaded = operator
// POSTCONDITION: Utilzing the private utility copy function the current AsymPattern object will take data from src
//				  only if the two objects do not share the same address. The new AsymPattern object will be returned
AsymPattern &AsymPattern::operator=(const AsymPattern& src) {
  if (this == &src) { return *this; } // guard clause
  copy(src);
  return *this;
}

// PRECONDITION: A valid AsymPattern object is given and compared with the current object to verify if their
//				 sequences are the same, otherwise false will be returned. OriginalSequences will not be compared,
// 				 only the current sequences within each object will be looked at.
// POSTCONDITION: No data is altered, a boolean will be returned depending on the equality of the currently active
// 				  sequence within the AsymPattern objects
bool AsymPattern::operator==(const AsymPattern& src) {
  if (size_ != src.size_) { return false; }

  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < sequences_[i].getSize(); j++) {
      if (sequences_[i][j] != src.sequences_[i][j])
        return false;
    }
  }

  return true;
}

// PRECONDITION: If both AsymPattern objects should not have the same sequence values and length, != will return true
// POSTCONDITION: No data is altered, a boolean will be returned depending on the equality of the currently active
// 				  sequence within the AsymPattern objects
bool AsymPattern::operator!=(const AsymPattern& src) {
  return !(*this == src); // negate == operation
}

// POST & PRE DECREMENT: Will share the same behavior
// PRECONDIITON: A valid AsymPattern object is given. For pre-increment all sequence values of the object will be incremented by 1
// POSTCONDITION: All values within the AsymPattern object will be incremented by 1
void AsymPattern::operator++() {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < sequences_[i].getSize(); j++) {
      sequences_[i].getSequence()[j]++;
    }
  }
}

// PRECONDIITON: A valid arith AsymPattern is given. For post-increment all sequence values of the object will be incremented by 1
// POSTCONDITION: All values within the AsymPattern object will be incremented by 1
void AsymPattern::operator++(int) {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < sequences_[i].getSize(); j++) {
      sequences_[i].getSequence()[j]++;
    }
  }
}

// POST & PRE DECREMENT: Will share the same behavior
// PRECONDIITON: A valid AsymPattern object is given. For pre-decrement all sequence values of the object will be decremented by 1
// POSTCONDITION: All values within the AsymPattern object will be decremented by 1
void AsymPattern::operator--() {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < sequences_[i].getSize(); j++) {
      sequences_[i].getSequence()[j]--;
    }
  }
}

// PRECONDIITON: A valid arith AsymPattern is given. For post-decrement all sequence values of the object will be decremented by 1
// POSTCONDITION: All values within the AsymPattern object will be decremented by 1
void AsymPattern::operator--(int) {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < sequences_[i].getSize(); j++) {
      sequences_[i].getSequence()[j]--;
    }
  }
}

// PRECONDIITON: A valid arith AsymPattern is given with a valid index passed into the method. If an invalid index is given,
//				 an exception will be thrown to the client
// POSTCONDITION: The [] accessor will return the ArithSeq shared_ptr from the index of AsymPattern, accessed by [index]
shared_ptr<int[]> AsymPattern::operator[](int index) {
	if (index > size_ || index < 0) { throw invalid_argument("AsymPattern index is out of bounds!"); }
   	return sequences_[index].getSequence();
}

// PRECONDIITON: A valid arith AsymPattern is given with a valid index passed into the method.
// POSTCONDITION: The << accessor will print all of the ArithSeq objects from AsymPattern
ostream& operator<<(ostream& out, const AsymPattern& a) {
  for (int i = 0; i < a.size_; i++) {
    out << "Sequence[" << i << "]: ";
    for (int j = 0; j < a.sequences_[i].getSize(); j++) {
      out << a.sequences_[i][j] << " ";
    }
    out << endl;
  }

  return out;
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

// PRECONDITION: src is a potentially modified AsymPattern object of length '.Length'
// POST-CONDITION: DeepCopy will copy values from src into original object to modify the sequence
bool AsymPattern::seqExists(int key) {
    if (key >= 0 && key < size_) { return true; }
    return false;
}

bool AsymPattern::atCapacity() {
  return size_ <= MAX_CAPACITY;
}

// PRECONDITION: On construction of the AsymPattern object, a copy was created to store the originalSequence_
//               of the sequence_ that has been modified over the life of the object.
// POST-CONDITION: Utilizing the stored copy originalSequence_, data for the original sequence_ will be released
//                 and a sequence_ will be constructed with the original size and data from initial sequence copy
void AsymPattern::reset() {
    size_ = originalSize_;

    //sequences_ = new ArithSeq* [size_];
    for (int i = 0; i < size_; i++) {
        sequences_[i] = originalSequences_[i];
    }
}

// PRECONDITION: seq is an ArithSeq object of length '_size', if current object is at capacity or key
//               is out of bounds, an exception will be thrown
// POST-CONDITION: Given a key to access the ArithSeq object within sequences_, the sequence will be reassigned
//                 to the parameter passed into AddArithSeq, seq.
void AsymPattern::addArithSeq(ArithSeq& seq, int key) {
    if (atCapacity() && key >= MAX_CAPACITY-1) {
        throw invalid_argument("Adding sequence out of bounds not allowed. Please overwrite existing memory.");
    }

    if (key < 0) {
        throw invalid_argument("Add Error: accessing invalid sequence key");
    }

    if (key >= size_) {
      throw invalid_argument("Invalid size: Provide a key within bounds");
    }

    sequences_[key] = *&seq;
}

// PRECONDITION: Current object invoking SetArithSeq must have an existing sequence, key, or else an exception is
//               thrown.
// POST-CONDITION: Given a key to access the ArithSeq object within sequences_, the sequence will be modified
//                 to the parameters passed into AddArithSeq, p and q.
void AsymPattern::setArithSeq(int p, int q, int key) {
    if (!seqExists(key)) {
    	throw invalid_argument("Set Error: Invalid key for accessing ArithSeq");
    }

    sequences_[key].modifySequence(p,q);
}

// PRECONDITION: Current object invoking ResetSeq must have an existing sequence, key, or else an exception is
//               thrown.
// POST-CONDITION: Given a key to access the ArithSeq object within sequences_, the sequence will be reset
//                 to its original state before modification.
void AsymPattern::resetSeq(int key) {
    if (!seqExists(key)) {
        throw invalid_argument("Reset Error: Invalid key for accessing ArithSeq");
    }

    sequences_[key].reset();
}

/*
* Implementation invariants:
* 1. MAX_CAPACITY limits the array size to 10 for efficiency and to prevent excessive heap usage. The constructor
 *   will enforce this and will throw an exception if invalid size passed.
* 2. Public methods for AsymPattern (resetSeq, setArithSeq, addArithSeq, seqExists) require a valid key to access the
 *   internal pattern, ArithSeq of the AsymPattern object. If an invalid key is provided, an exception will be thrown.
* 3. Reset() restores a valid key sequences to its original state.
* 4. Copying is suppressed, and only reserved for move semantics.
 * 	 Private members cannot be accessed outside the class, any attempt to copy AsymPattern will fail at compile time
* 5. "In C++17 it is recommended that the form array form std::shared_ptr<T[]> should be used rather than
* 		constructing a std::shared_ptr<T> from a std::unique_ptr<T[]> in C++11 and C++14" - cppreference
* 6. AsymPattern supports ==/!= operators, post/pre-fix operators for incrementation and subtraction (++/--), and
 * 		the [] accessor which will return an shared_ptr belonging to the ArithSeq object. AsymPattern does
 * 		fully support integer addition through +=/+ operators, it is also compatible with other AsymPattern objects.
* 		The << operator has been overloaded to support smart printing of ArithSeq objects as well as its index.
* 		The >> has not been overloaded due to the flexibility of using +/+= to write data to the object.
*/
