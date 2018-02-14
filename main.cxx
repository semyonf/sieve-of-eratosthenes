/**
 * Copyright 2018, Semyon Fomin
 */

#include <vector>
#include <cmath>

struct Block {
    unsigned long data; unsigned last;
};

unsigned long dataCell = 0xffffffff;

short amountOfBlocks = 5000,
    blockSize = static_cast<short>(floor(log2(dataCell))) + 1;

unsigned getMask(unsigned n, unsigned last) {
  unsigned mask = 0;
  for (unsigned i = last - blockSize + 1; i <= last; ++i)
    if (i % n != 0)
        mask += 1 << (last - i);

  return mask;
}

int main() {
    std::vector<Block> blocks;
    std::vector<int> primes;

    for (short i = 0; i < amountOfBlocks; ++i)
        blocks.push_back({
            dataCell,
            static_cast<unsigned>(blockSize + 1 + (i * blockSize))
        });

    printf("%lu blocks of %d bits\n", blocks.size(), blockSize);

    unsigned long curBlock = 0;
    int newPrime;
    Block block;

    while (curBlock < blocks.size()) {
        block = blocks[curBlock];

        newPrime = (block.data == 0)
            ? block.last
            : block.last - floor(log2(block.data));

        primes.push_back(newPrime);

        for (unsigned long i = curBlock; i < blocks.size(); ++i) {
            block = blocks[i];
            blocks[i].data = block.data & getMask(newPrime, block.last);
        }

        if (blocks[curBlock].data == 0)
            ++curBlock;
    }

    for (unsigned long i = 0; i < primes.size(); ++i)
        printf("%d ", primes[i]);

    printf("\n(%lu) items\n", primes.size());
}
