/* Jeremy Hernandez
 ArithSeq.cs
 1/14/2025
 
 Class Invariants:
    1. Setting the maximum number of operations for Arith Seq must be at least 30, 
        which will be set automatically within the constructor if a valid value is not given. 
    2. The length of the ArithSeq must always be greater than 0. The constructor will 
        throw an error if an invalid length value (0 => n) is given.
    3. A valid difference for the construction of the object, and for the modify method, This prevents
        an invalid sequence to form, or no changes to be made.
    4. The original sequence value is used to keep track of the sequence before any operations can be made.
        This is required in order to return the sequence to its original state after Reset(). 
*/

namespace ArithSeq
{
    public class ArithSeq
    {
        private int[] sequence;
        private int[] originalSequence;
        private int operations;
        private int maxOperations;
        private readonly int firstTerm;
        private readonly int diff;
        private readonly int len;

        // ArithSeq()
        // PRECONDITIONS:
            // firstTerm is an integer, can be anything
            // difference is an integer, must be greater than 0
            // sequenceLength is an integer, must be greater than 0
            // maxOp is an optional parameter, it must be greater than 0 if provided
        // POSTCONDITIONS:
            // the arithSeq object has been initialized with a valid arithmetic sequence 
            // operations is set to zero
            // originalSequence is a shallow copy of the sequence array for resetting state of object with Reset()
        public ArithSeq(int firstTerm, int difference, int sequenceLength, int maxOp = 30)
        {

            if (sequenceLength <= 0)
            {
                throw new ArgumentException("Sequence length must be greater than or equal to 0");
            }

            if (maxOperations < 0)
            {
                throw new ArgumentException("Max operations must be greater than 0");
            }

            if (difference <= 0)
            {
                throw new ArgumentException("Difference must be greater than 0");
            }

            // validated inputs, set fields
            firstTerm = firstTerm;
            diff = difference;
            len = sequenceLength;
            maxOperations = maxOp;

            sequence = new int[len];
            // calculate each term of the sequence
            for (int i = 0; i < len; i++)
            {
                sequence[i] = firstTerm + i * diff;
            }

            // shallow copy
            originalSequence = new int[len];
            for (int i = 0; i < len; i++)
            {
                originalSequence[i] = sequence[i];
            }

            operations = 0;
        }

        private void ExceedsMaxOperations()
        {
            if (operations >= maxOperations)
            {
                throw new ArgumentException("Exceeded max operations");
            }

            operations++;
        }
        
        // public query regarding state
        bool canPerformMoreOperations() {
            return operations < maxOperations;
        }

        public int[] GetSequence()
        {
            if (sequence.Length == 0)
            {
                throw new ArgumentException("Sequence is empty");
            }

            return sequence;
        }

        public int GetKthValue(int k)
        {
            if (k < 0 || k >= GetSequence().Length)
            {
                throw new ArgumentException("K must be between 0 and sequence length");
            }

            ExceedsMaxOperations();
            return GetSequence()[k];
        }

        public int DivisibleBy(int divisor)
        {
            if (divisor == 0)
            {
                throw new ArgumentException("Divisor must not equal 0");
            }

            int count = 0;
            for (int i = 0; i < sequence.Length; i++)
            {
                if ((sequence[i] % divisor) == 0)
                {
                    count++;
                }
            }

            ExceedsMaxOperations();
            return count;
        }

        // PRECONDITION: arithSeq is a potentially modified sequence of length 'n'
        // POSTCONDITION: sequence will modify values from parameters, p and q, to modify the sequence
        public void ModifySequence(int p, int q)
        {
            if (p < 0 || p >= sequence.Length)
            {
                throw new ArgumentException("p must be between 0 and sequence length");
            }

            if (q == 0) return;

            for (int i = p; i <len; i += (p == 0 ? 1 : q)) 
            { // user can change sequence from 0
                sequence[i] += q;
            }
            
            ExceedsMaxOperations();
        }

        // PRECONDITION: arithSeq is a potentially modified sequence of length 'n'
        // POSTCONDITION: sequence will copy values from originalSequence to Reset the sequence
        public void Reset()
        {
            for (int i = 0; i < originalSequence.Length; i++)
            {
                sequence[i] = originalSequence[i];
            }

            operations = 0;
        }
    }
}

/*
 * Implementation Invariant:
 *  1. The maxOperations variable must always be 30 >=. If this is not provided within the constructor it will default.
 *  2. The length of the sequence, n, must always be greater than 0.
 *  3. The difference between terms, diff, must always be greater than 0.
 *  4. The originalSequence array will always be equal to the initial state of sequence when it is constructed.
 *  5. The sequence array will always have the same length as 'n', and reflect values from the initial sequence formula.
 *     Deviations to the original sequence formula will be performed by the ModifySequence method.
 */