/**
 * Copyright 2018, Semyon Fomin
 */

#include <cmath>
#include <vector>

const int amountOfBlocks = 5000;
const unsigned long dataCell = 0xffffffff;
const int blockSize = (int(log2(dataCell)) + 1) << 0;

struct DataBlock {
    unsigned long data;
    int number;
    int lastNumber;
    int firstNumber;
};

std::vector<DataBlock> blocks;
std::vector<int> primes;

int getMask(int prime, int lastNumber, int firstNumber) {
    unsigned long mask = dataCell;
    for (int number = firstNumber; number <= lastNumber; ++number) {
        if (number % prime == 0) {
            mask -= 1 << (lastNumber - number);
        }
    }

    return mask;
}

int main() {
    printf("%d blocks of %d bits\n", amountOfBlocks, blockSize);

    for (int i = 0; i < amountOfBlocks; ++i) {
        blocks.push_back({
            dataCell, i, blockSize + 1 + (i * blockSize), 2 + (i * blockSize)
        });
    }
    
    int currentBlockNumber = 0;
    DataBlock block;
    int newPrime;

    while (currentBlockNumber < amountOfBlocks) {
        if (blocks[currentBlockNumber].data == 0) {
          ++currentBlockNumber;
          continue;
        }

        block = blocks[currentBlockNumber];
        newPrime = block.lastNumber - (int(log2(block.data)) << 0);
        primes.push_back(newPrime);

        for (int i = currentBlockNumber; i < amountOfBlocks; ++i) {
          blocks[i].data = blocks[i].data & getMask(
            newPrime, blocks[i].lastNumber, blocks[i].firstNumber
          );
        }
    }

    for (unsigned long i = 0; i < primes.size(); ++i) {
        printf("%d ", primes[i]);
    }

    printf(" (%lu) items\n", primes.size());
}
