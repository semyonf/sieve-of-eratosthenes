/**
 * Copyright 2018, Semyon Fomin
 */

const amountOfBlocks = 5000;

const blocks = [], primes = [];
const dataCell = 0xffffffff;
const blockSize = Math.floor(Math.log2(dataCell)) + 1;

for (let i = 0; i < amountOfBlocks; ++i) {
  blocks.push({
    data: dataCell, last: blockSize + 1 + (i * blockSize)
  });
}

let curBlock = 0, block, newPrime;

while (curBlock < blocks.length) {
  block = blocks[curBlock];

  newPrime = block.last - Math.floor(Math.log2(block.data));
  primes.push(newPrime);

  for (let i = 0; i < blocks.length; ++i) {
    block = blocks[i];
    blocks[i].data = block.data & getMask(newPrime, block.last);
  }

  if (blocks[curBlock].data === 0) {
    ++curBlock;
  }
}

function getMask(n, last) {
  let mask = 0;
  for (let i = last - blockSize; i <= last; ++i) {
    if (i % n) {
      mask += Math.pow(2, last - i);
    }
  }

  return mask;
}

// primes.forEach(prime => console.log(prime));
console.log(primes.pop(), primes.length);
