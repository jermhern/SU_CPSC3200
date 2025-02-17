/*
 * Class Invariants:
 * 1. File integrity
 *      - fileName must always contain a valid file path, or else an exception will be thrown
 *      - changes must be a valid and open FileStream object
 *      - writer must be a valid StreamWriter instance associated
 *        with changes
 * 2. Valid Sequences
 *      - sequences must always contain valid arithSeq objects, or else an exeception will be thrown.
 *      - The size of sequences should always match size (from AsymPattern)
 *      - sequences should not contain null references, or else an exception will be thrown.
 *      - AddArithSeq should not allow insertion beyond the maximum allowed capacity,
 *        or else an exception will be thrown
 *      - SetArithSeq and Reset should only modify exisiting sequences, ensure the key exists
 *        or else an exception will be thrown.
 * 3. Data consistency
 *      - Any modification to an DurableSeq object within sequences will be logged in the corresponding
 *        file.
 *      - bulkChange is cleared after every write to the file to prevent data corruption, or overwriting.
 * 4. File management
 *      - The file should remain open while DurableSeq is in use and
 *        should be closed when Dispose() is called.
 *      - Changes to the file will be reflected when Dispose() is called.
 */

#include "DurableSeq.h"

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
 *  7. Dispose() should properly close the StreamWriter to prevent memory leaks and data not being written.
 *      Any attempts to write to the file after Dispose will result in an error.
 */