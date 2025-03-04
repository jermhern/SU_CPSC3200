//
// Updated by Jeremy on 3/2/25.
// Header file in C++ for DurableSeq
//

#ifndef DURABLESEQ_H
#define DURABLESEQ_H

#include "AsymPattern.h"
#include "DurableSeq.h"
#include <fstream>
#include <string>

class DurableSeq: public ArithSeq {
    public:
        DurableSeq(ArithSeq* sequence, int size = 10, string changes = "name");
        DurableSeq(const DurableSeq&); // Copy Constructor
        DurableSeq(DurableSeq&& src); // move
        ~DurableSeq();

        void replicate(ArithSeq&);
        void reset() override;

        void addArithSeq(ArithSeq&, int key);
        void setArithSeq(int p, int q, int key);
        void resetSeq(int key);
        bool seqExists(int key); // public query regarding state

        // operator overloading
        bool operator==(const DurableSeq&);
        bool operator!=(const DurableSeq&);
        void operator++() override;
        void operator++(int) override;
        void operator--() override;
        void operator--(int) override;
        ArithSeq operator[](int);
        friend ostream& operator<<(ostream&, const DurableSeq&);

    private:
        shared_ptr<ArithSeq[]> sequences_;
        shared_ptr<ArithSeq[]> originalSequences_;

        int size_;
        int originalSize_;

        string fileName;
        string bulkChanges;
        ofstream fin;

        // Suppress copying
        DurableSeq& operator=(const DurableSeq&); // Overloaded Assignment Operator
        DurableSeq& operator=(DurableSeq&&); // move

        bool atCapacity();
        const int MAX_CAPACITY = 10;
        void writeData(ArithSeq&);
        void copy(const DurableSeq& src);
};



#endif //DURABLESEQ_H
