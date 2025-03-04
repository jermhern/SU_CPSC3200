//
// Updated by Jeremy on 3/2/25.
// Implementation file in C++ for DurableSeq
//

#include "DurableSeq.h"
#include "AsymPattern.h"
#include "ArithSeq.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

/*
 * Class Invariants:
 * 1. File integrity
 *      - fileName must always contain a valid file path, or else an exception will be thrown
 *      - changes must be a valid and open FileStream object
 *      - writer must be a valid StreamWriter instance associated
 *        with changes
 * 2. Valid Sequences
 *      - sequences must always contain valid arithSeq objects, or else an exeception will be thrown.
 *      - The size of sequences should always match size (from DurableSeq)
 *      - sequences should not contain null references, or else an exception will be thrown.
 *      - AddDurableSeq should not allow insertion beyond the maximum allowed capacity,
 *        or else an exception will be thrown
 *      - SetDurableSeq and Reset should only modify exisiting sequences, ensure the key exists
 *        or else an exception will be thrown.
 * 3. Data consistency
 *      - Any modification to an DurableSeq object within sequences will be logged in the corresponding
 *        file.
 *      - bulkChange is cleared after every write to the file to prevent data corruption, or overwriting.
 * 4. File management
 *      - The file should remain open while DurableSeq is in use and
 *        should be closed when Dispose() is called.
 *      - Changes to the file will be reflected when Dispose() is called.
*  5. Overloaded Operators
* 	- >> will not be overloaded as operators +, += have been provided to stream data into the desired object
* 	- the << operator provides a convenient way to print all of the ArithSeq objects that are present within the current
* 	  DurableSeq object with information to view index as well
* 	- The +, += operators will work with other DurableSeq objects due to their complexity
 *  - The post/pre-fix operators ++ and -- will increment or decrement every value, in every ArithSeq object, by 1
* 	- Equality operators ==/!= have been provided and return a boolean regarding the equality of the DurableSeq Objects
* 	- the [] accessor has been overloaded which provides a way to return a ArithSeq to the valid index provided
 */


// DurableSeq()
// PRECONDITIONS:
// sequences is an ArithSeq object, it must contain sequences, and be within bound, or else an exception is thrown
// name must contain a valid name for a .txt document, or else an exception will be thrown
// name must be less than 15 characters to prevent long filenames, or else an exception will be thrown
// POST-CONDITIONS:
// FStream, changes, will look to open or create a new file that matches the .txt file provided
// the DurableSeq object has been initialized with a valid ArithSeq array
DurableSeq::DurableSeq(ArithSeq* sequences, int size, string name): sequences_(), originalSequences_()
{
    if (size == 0) throw invalid_argument("Null ArithSeq Dependency received");
    if (sequences == nullptr) throw invalid_argument("Null filename received");
    if (name.length() == 0) throw invalid_argument("Empty filename received");
    if (name.length() >= 15) throw invalid_argument("Filename must be less than 15 characters");

    // inject via constructor
    this->size_ = size;
    this->originalSize_ = size;

    sequences_ = shared_ptr<ArithSeq[]>(new ArithSeq[size_]);
    originalSequences_ = shared_ptr<ArithSeq[]>(new ArithSeq[size_]);

    for (int i = 0; i < size_; i++) {
        // DurableSeq will not own objects
        sequences_[i] = sequences[i];
        originalSequences_[i] = sequences[i];
    }

    fileName = name + ".txt";
    fin.open(fileName.c_str());
    if (fin.fail()) {
        throw invalid_argument("Error creating/opening" + fileName);
    }
}

// PRECONDITION: destructor is no longer needed as dynamic memory is managed by smart pointers
DurableSeq::~DurableSeq() {
  cout << fileName << " file has been closed." << endl;
  fin.close();
}

// WriteData()
// PRECONDITION: seq is a potentially modified DurableSeq object of length '.Length'. There is a valid changes.txt
//               file created or opened that will be written to with changes to ArithSeq Objects
// POST-CONDITION: WriteData() will write to the file open or created from DurableSeq(). The data written to the
//                 file will occur from any changes made to seq.
void DurableSeq::writeData(ArithSeq &sequence) {

    for (int i = 0; i < sequence.getSize(); i++)
    	bulkChanges += std::to_string(sequence.getSequence().get()[i]) + " ";

    fin << bulkChanges << endl;
    bulkChanges = "";
}

// PRECONDITION: A valid DurableSeq object is given and compared with the current object to verify if their
//				 sequences are the same, otherwise false will be returned. OriginalSequences will not be compared,
// 				 only the current sequences within each object will be looked at.
// POSTCONDITION: No data is altered, a boolean will be returned depending on the equality of the currently active
// 				  sequence within the DurableSeq objects
bool DurableSeq::operator==(const DurableSeq& src) {
  if (size_ != src.size_) { return false; }

  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < sequences_[i].getSize(); j++) {
      if (sequences_[i][j] != src.sequences_[i][j])
        return false;
    }
  }

  return true;
}

// PRECONDITION: If both DurableSeq objects should not have the same sequence values and length, != will return true
// POSTCONDITION: No data is altered, a boolean will be returned depending on the equality of the currently active
// 				  sequence within the DurableSeq objects
bool DurableSeq::operator!=(const DurableSeq& src) {
  return !(*this == src); // negate == operation
}

// POST & PRE DECREMENT: Will share the same behavior
// PRECONDIITON: A valid DurableSeq object is given. For pre-increment all sequence values of the object will be incremented by 1
// POSTCONDITION: All values within the DurableSeq object will be incremented by 1, and changes will be writted to file
void DurableSeq::operator++() {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < sequences_[i].getSize(); j++) {
      sequences_[i].getSequence()[j]++;
    }
    writeData(sequences_[i]);
  }
}

// PRECONDIITON: A valid arith DurableSeq is given. For post-increment all sequence values of the object will be incremented by 1
// POSTCONDITION: All values within the DurableSeq object will be incremented by 1, and changes will be writted to file
void DurableSeq::operator++(int) {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < sequences_[i].getSize(); j++) {
      sequences_[i].getSequence()[j]++;
    }
    writeData(sequences_[i]);
  }
}

// POST & PRE DECREMENT: Will share the same behavior
// PRECONDIITON: A valid DurableSeq object is given. For pre-decrement all sequence values of the object will be decremented by 1
// POSTCONDITION: All values within the DurableSeq object will be decremented by 1, and changes will be writted to file
void DurableSeq::operator--() {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < sequences_[i].getSize(); j++) {
      sequences_[i].getSequence()[j]--;
    }
    writeData(sequences_[i]);
  }
}

// PRECONDIITON: A valid arith DurableSeq is given. For post-decrement all sequence values of the object will be decremented by 1
// POSTCONDITION: All values within the DurableSeq object will be decremented by 1, and changes will be writted to file
void DurableSeq::operator--(int) {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < sequences_[i].getSize(); j++) {
      sequences_[i].getSequence()[j]--;
    }
    writeData(sequences_[i]);
  }
}

// PRECONDIITON: A valid arith DurableSeq is given with a valid index passed into the method. If an invalid index is given,
//				 an exception will be thrown to the client
// POSTCONDITION: The [] accessor will return the DurableSeq ArithSeq from the index of DurableSeq, accessed by [index]
ArithSeq DurableSeq::operator[](int index) {
	if (index > size_ || index < 0) { throw invalid_argument("DurableSeq index is out of bounds!"); }
   	return sequences_[index];
}

// PRECONDIITON: A valid arith DurableSeq is given with a valid index passed into the method.
// POSTCONDITION: The << accessor will print all of the ArithSeq objects from DurableSeq
ostream& operator<<(ostream& out, const DurableSeq& a) {
  for (int i = 0; i < a.size_; i++) {
    out << "Sequence[" << i << "]: ";
    for (int j = 0; j < a.sequences_[i].getSize(); j++) {
      out << a.sequences_[i][j] << " ";
    }
    out << endl;
  }

  return out;
}

// reset()
// PRECONDITION: On construction of the DurableSeq object, a copy was created to store the originalSequence_
//               of the sequence_ that has been modified over the life of the object.
// POST-CONDITION: Utilizing the stored copy originalSequence_, data for the original sequence_ will be released
//                 and a sequence_ will be constructed with the original size and data from initial sequence copy
void DurableSeq::reset() {
  size_ = originalSize_;

  //sequences_ = new ArithSeq* [size_];
  for (int i = 0; i < size_; i++) {
      sequences_[i] = originalSequences_[i];
  }

  // empty the file by using trunc, which will truncate length of the open file to 0
  fin.close();
  fin.open(fileName, std::ios::out | std::ios::trunc);
}

// AddArithSeq()
// PRECONDITION: seq is an ArithSeq object of length 'size', if current object is at capacity or key
//               is out of bounds, an exception will be thrown
// POST-CONDITION: Given a key to access the ArithSeq object within sequences_, the sequence will be reassigned
//                 to the parameter passed into AddArithSeq, seq. Additionally, any changes made will be written
//                 to the existing file utilizing WriteData().
void DurableSeq::addArithSeq(ArithSeq &sequence, int key) {
    if (atCapacity() && key >= MAX_CAPACITY-1) {
        throw invalid_argument("Adding sequence out of bounds not allowed. Please overwrite existing memory.");
    }

    if (key < 0) {
        throw invalid_argument("Add Error: accessing invalid sequence key");
    }

    if (key >= size_) {
      throw invalid_argument("Invalid size: Provide a key within bounds");
    }

    sequences_[key] = *&sequence;

    writeData(sequence);
}

// SetArithSeq()
// PRECONDITION: Current object invoking SetArithSeq must have an existing sequence, key, or else an exception is
//               thrown.
// POST-CONDITION: Given a key to access the ArithSeq object within sequences_, the sequence will be modified
//                 to the parameters passed into AddArithSeq, p and q. Additionally, any changes made will be
//                 written to the existing file utilizing WriteData().
void DurableSeq::setArithSeq(int p, int q, int key) {
    if (!seqExists(key)) {
    	throw invalid_argument("Set Error: Invalid key for accessing ArithSeq");
    }

    sequences_[key].modifySequence(p,q);
    writeData(sequences_[key]);
}

// resetSeq() puts the sequence and file back in their original states.
// PRECONDITION: Current object invoking ResetSeq must have an existing sequence, key, or else an exception is
//               thrown.
// POST-CONDITION: Given a key to access the ArithSeq object within sequences_, the sequence will be reset
//                 to its original state before modification. Additionally, any changes made will be
//                 written to the existing file utilizing WriteData().
void DurableSeq::resetSeq(int key) {
    if (!seqExists(key)) {
        throw invalid_argument("Reset Error: Invalid key for accessing ArithSeq");
    }

    sequences_[key].reset();
    writeData(sequences_[key]);
}

bool DurableSeq::atCapacity() {
  return size_ <= MAX_CAPACITY;
}

// PRECONDITION: src is a potentially modified DurableSeq object of length '.Length'
// POST-CONDITION: DeepCopy will copy values from src into original object to modify the sequence
bool DurableSeq::seqExists(int key) {
    if (key >= 0 && key < size_) { return true; }
    return false;
}

/*
 * Implementation Invariants
 *  1. The sequences array must not be empty
 *  2. The name for the file must be a valid strong between 1 and 14 characters
 *  3. If the file does not exist, one will be created, otherwise it will be opened and overwritten
 *  4. Writes containing sequence changes will occur unless DeepCopy is called, which will then reflect the
 *     changes of the sequence to be copied.
 *  5. AddArithSeq should not allow insertion beyond the maximum allowed capacity,
 *        or else an exception will be thrown
 *  6. SetArithSeq and Reset should only modify exisiting sequences, ensure the key exists
 *        or else an exception will be thrown.
*   7. Copying is suppressed, and only reserved for move semantics.
 * 	 Private members cannot be accessed outside the class, any attempt to copy DurableSeq will fail at compile time
* 	8. "In C++17 it is recommended that the form array form std::shared_ptr<T[]> should be used rather than
 * 		constructing a std::shared_ptr<T> from a std::unique_ptr<T[]> in C++11 and C++14" - cppreference
*  9. DurableSeq supports ==/!= operators, post/pre-fix operators for incrementation and subtraction (++/--), and
 * 		the [] accessor which will return an shared_ptr belonging to the ArithSeq object. Although DurableSeq does not
 * 		fully support integer addition through +=/+ operators, it is compatible with other DurableSeq objects
 */