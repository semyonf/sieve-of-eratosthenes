/**
 * Copyright 2018, Semyon Fomin
 */

const amountOfBlocks = 5000;

const blocks = [], primes = [];
const dataCell = 0xffffffff;
const blockSize = Math.floor(Math.log2(dataCell)) + 1;

console.info(`${amountOfBlocks} blocks of ${blockSize} bits`);

for (let i = 0; i < amountOfBlocks; ++i) {
  blocks.push({
    data: dataCell, last: blockSize + 1 + (i * blockSize)
  });
}

let curBlock = 0, block, newPrime;

while (curBlock < amountOfBlocks) {
  if (blocks[curBlock].data === 0) {
    ++curBlock;
    continue;
  }

  block = blocks[curBlock];

  newPrime = block.last - ((Math.log2(block.data)) << 0);
  primes.push(newPrime);

  for (let i = curBlock; i < amountOfBlocks; ++i) {
    block = blocks[i];
    blocks[i].data = block.data & getMask(newPrime, block.last);
  }
}

function getMask(prime, last) {
  let mask = dataCell;
  for (let number = last - blockSize + 1; number <= last; ++number) {
    if (number % prime === 0) {
      mask -= 1 << (last - number);
    }
  }

  return mask;
}

let res = '';

primes.forEach(prime => res += `${prime} `);

console.info(res);
console.info(`(${primes.length}) items`);
