/**
 * Copyright 2018, Semyon Fomin
 *
 * Parallel Sieve of Eratosthenes implementation using bit packing and OpenMP.
 *
 * This implementation uses a block-based approach where each block stores 32 numbers
 * as bits in an unsigned integer. The algorithm marks composite numbers by clearing
 * their corresponding bits, leaving only primes set.
 */

#include <cmath>
#include <vector>
#include <cstdio>
#include <climits>

// Number of bits per block (32 bits for unsigned int)
const int BITS_PER_BLOCK = sizeof(unsigned) * CHAR_BIT;
const unsigned ALL_BITS_SET = ~0u;  // All bits set to 1 (potential primes)

// Configuration: number of blocks to use (determines range of primes)
const int amountOfBlocks = 5000;  // ~15000 primes, 7030 for first 20000 primes

/**
 * DataBlock structure represents a segment of numbers as a bitmask.
 * Each bit position represents whether a number is potentially prime (1) or composite (0).
 */
struct DataBlock {
    unsigned data;        // Bitmask where each bit represents a number's primality
    int blockIndex;       // Index of this block
    int lastNumber;       // Last number represented in this block
    int firstNumber;      // First number represented in this block
};

std::vector<DataBlock> blocks;
std::vector<int> primes;

/**
 * Generates a bitmask for marking multiples of a prime as composite.
 *
 * @param prime The prime number whose multiples should be marked
 * @param lastNumber The last number in the block range
 * @param firstNumber The first number in the block range
 * @return Bitmask with bits cleared for multiples of prime
 */
unsigned getMask(int prime, int lastNumber, int firstNumber) {
    unsigned mask = ALL_BITS_SET;

    // Find the first multiple of prime in this block's range
    // Start from prime*prime (smaller multiples already marked by smaller primes)
    int startNumber = ((firstNumber + prime - 1) / prime) * prime;
    if (startNumber < prime * prime) {
        startNumber = prime * prime;
    }

    // Mark all multiples of prime in this block as composite
    for (int number = startNumber; number <= lastNumber; number += prime) {
        if (number >= firstNumber && number <= lastNumber) {
            int bitPosition = lastNumber - number;
            // Bounds check to prevent undefined behavior
            if (bitPosition >= 0 && bitPosition < BITS_PER_BLOCK) {
                mask &= ~(1u << bitPosition);
            }
        }
    }

    return mask;
}

/**
 * Extracts the next prime number from a bitmask.
 *
 * @param data The bitmask to search
 * @param lastNumber The last number represented in the mask
 * @param startBit The bit position to start searching from
 * @return The prime number found, or -1 if no prime in this mask
 */
int extractPrimeFromMask(unsigned data, int lastNumber, int startBit = 0) {
    // Find the first set bit (potential prime) starting from startBit
    for (int bit = startBit; bit < BITS_PER_BLOCK; ++bit) {
        if (data & (1u << bit)) {
            return lastNumber - bit;
        }
    }
    return -1;  // No prime found
}

int main() {
    printf("Sieve of Eratosthenes: %d blocks of %d bits each\n",
           amountOfBlocks, BITS_PER_BLOCK);

    // Initialize blocks - each block represents BITS_PER_BLOCK consecutive numbers
    // Start from 2 (first prime), so block 0 represents numbers [2, 33]
    for (int i = 0; i < amountOfBlocks; ++i) {
        int firstNum = 2 + (i * BITS_PER_BLOCK);
        int lastNum = firstNum + BITS_PER_BLOCK - 1;
        blocks.push_back({
            ALL_BITS_SET,  // All numbers initially marked as potential primes
            i,
            lastNum,
            firstNum
        });
    }

    // Main sieve algorithm
    // First, find all primes up to sqrt of our maximum number
    int maxNumber = blocks[amountOfBlocks - 1].lastNumber;
    int sqrtMax = static_cast<int>(sqrt(maxNumber)) + 1;

    // Extract all primes and mark composites
    for (int blockIdx = 0; blockIdx < amountOfBlocks; ++blockIdx) {
        unsigned data = blocks[blockIdx].data;
        int lastNum = blocks[blockIdx].lastNumber;

        // Extract all primes from this block
        for (int bit = BITS_PER_BLOCK - 1; bit >= 0; --bit) {
            if (data & (1u << bit)) {
                int prime = lastNum - bit;
                primes.push_back(prime);

                // Only sieve if prime <= sqrt(maxNumber)
                if (prime <= sqrtMax) {
                    // Mark all multiples of this prime in subsequent blocks
                    #pragma omp parallel for schedule(dynamic) if(amountOfBlocks - blockIdx > 10)
                    for (int i = blockIdx; i < amountOfBlocks; ++i) {
                        unsigned mask = getMask(
                            prime,
                            blocks[i].lastNumber,
                            blocks[i].firstNumber
                        );
                        blocks[i].data &= mask;
                    }
                    // Update current block's data after sieving
                    data = blocks[blockIdx].data;
                }
            }
        }
    }

    // Output results
    printf("Found primes:\n");
    for (size_t i = 0; i < primes.size(); ++i) {
        printf("%d ", primes[i]);
        // Add line breaks every 20 primes for readability
        if ((i + 1) % 20 == 0) {
            printf("\n");
        }
    }

    printf("\n\nTotal: %zu prime numbers found\n", primes.size());

    return 0;
}
