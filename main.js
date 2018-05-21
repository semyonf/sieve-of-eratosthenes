/**
 * Copyright 2018, Semyon Fomin
 */

const amountOfBlocks = 5000;
const dataCell = 0xffffffff;
const blocks = [], primes = [];
const blockSize = Math.log2(dataCell) + 1 << 0;

console.info(`${amountOfBlocks} blocks of ${blockSize} bits`);

for (let i = 0; i < amountOfBlocks; ++i) {
  blocks.push({
    data: dataCell,
    number: i,
    lastNumber: blockSize + 1 + (i * blockSize),
    firstNumber: 2 + (i * blockSize)
  });
}

let currentBlockNumber = 0, block, newPrime;

while (currentBlockNumber < amountOfBlocks) {
  if (blocks[currentBlockNumber].data === 0) {
    ++currentBlockNumber;
    continue;
  }

  block = blocks[currentBlockNumber];
  newPrime = block.lastNumber - ((Math.log2(block.data)) << 0);
  primes.push(newPrime);

  for (let i = currentBlockNumber; i < amountOfBlocks; ++i) {
    blocks[i].data = blocks[i].data & getMask(
      newPrime, blocks[i].lastNumber, blocks[i].firstNumber
    );
  }
}

function getMask(prime, lastNumber, firstNumber) {
  let mask = dataCell;
  for (let number = firstNumber; number <= lastNumber; ++number) {
    if (number % prime === 0) {
      mask -= 1 << (lastNumber - number);
    }
  }

  return mask;
}

let res = '';
primes.forEach(prime => res += `${prime} `);
console.info(res, `(${primes.length}) items`);
