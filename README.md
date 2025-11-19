# Sieve of Eratosthenes - Parallel Implementation

A high-performance, parallel implementation of the [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) algorithm for finding prime numbers, using C++17, OpenMP parallelization, and bit-packing optimization.

## Features

- **Parallel Processing**: Uses OpenMP for multi-threaded prime number generation
- **Memory Efficient**: Bit-packing technique stores 32 numbers per unsigned integer
- **Optimized Performance**: Compiler optimizations (-O3, -flto, -march=native)
- **Configurable Range**: Easily adjust the number of primes to generate
- **Cross-Platform**: Supports both Linux and macOS (Intel x86)

## What is the Sieve of Eratosthenes?

The Sieve of Eratosthenes is an ancient algorithm for finding all prime numbers up to a given limit. It works by iteratively marking the multiples of each prime as composite, starting from 2. This implementation uses a block-based approach with bit manipulation for enhanced performance.

## Requirements

### All Platforms
- **C++17 compatible compiler**
- **OpenMP library** (for parallel processing)
- **make** build tool

### Platform-Specific Requirements

#### macOS (Intel x86 only)

> **Warning**
> This will not work on Apple Silicon (M1/M2/M3) chips, Intel x86 only!

```sh
# Install OpenMP library
brew install libomp

# Install Xcode Command Line Tools (if not already installed)
xcode-select --install
```

You'll need [Xcode Command Line Tools](https://developer.apple.com/xcode/resources/)

#### Linux

Most Linux distributions include OpenMP with GCC by default. If needed:

```sh
# Debian/Ubuntu
sudo apt-get install build-essential

# Fedora/RHEL
sudo dnf install gcc-c++ make

# Arch Linux
sudo pacman -S gcc make
```

## Building and Running

### Quick Start

```sh
# Build and run the program
make cxx

# View the output
cat out/primes.txt
```

### Available Make Targets

```sh
# Build and run (default target)
make cxx

# Clean build artifacts
make clean
```

### Build Process

The Makefile automatically detects your platform and uses the appropriate compiler:
- **Linux**: Uses `g++` with standard OpenMP flags
- **macOS**: Uses `clang++` with macOS-specific OpenMP configuration

Compiler flags used:
- `-std=c++17` - C++17 standard
- `-O3` - Maximum optimization
- `-flto` - Link-time optimization
- `-march=native` - CPU-specific optimizations
- `-Wall -Wextra -pedantic` - Comprehensive warnings
- `-fopenmp` - OpenMP support

## Usage

### Basic Usage

```sh
make cxx
```

Output will be displayed in the terminal and saved to `out/primes.txt`.

### Configuration

To change the range of primes generated, edit `eratosthenes.cxx`:

```cpp
// Line 21: Adjust the number of blocks
const int amountOfBlocks = 5000;  // ~15000 primes up to ~160,000
```

**Block Count Guide:**
- 100 blocks → ~450 primes (up to ~3,200)
- 1000 blocks → ~2,800 primes (up to ~32,000)
- 5000 blocks → ~15,000 primes (up to ~160,000)
- 7030 blocks → ~20,000 primes (up to ~225,000)

### Output

The program generates two outputs:

1. **Console output** - Displays all found primes with formatting
2. **File output** - Saves primes to `out/primes.txt`

Example output:
```
Sieve of Eratosthenes: 5000 blocks of 32 bits each
Found primes:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71
73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 ...

Total: 15000 prime numbers found
```

## Project Structure

```
sieve-of-eratosthenes/
├── eratosthenes.cxx    # Main C++ source code
├── Makefile            # Build configuration
├── README.md           # This file
├── LICENSE             # MIT License
├── .gitignore          # Git ignore rules
├── bin/                # Compiled binary (generated)
│   └── eratosthenes
└── out/                # Output directory (generated)
    └── primes.txt
```

## Algorithm Overview

This implementation uses a block-based sieve with the following optimizations:

1. **Bit Packing**: Each block stores 32 numbers as bits in an unsigned integer
2. **Parallel Sieving**: OpenMP parallelizes the marking of composite numbers
3. **Optimized Range**: Only sieves with primes ≤ √(max_number)
4. **Memory Efficiency**: Represents 160,000 numbers using only ~5KB of memory

## Performance

Performance varies by CPU and block count:
- **100 blocks**: < 0.1 seconds
- **5000 blocks**: ~0.5-2 seconds
- **7030 blocks**: ~1-3 seconds

Multi-core CPUs will see significant speedup due to OpenMP parallelization.

## Troubleshooting

### macOS: "library not found for -lomp"

Install OpenMP via Homebrew:
```sh
brew install libomp
```

### Linux: Compilation fails with OpenMP errors

Install GCC and development tools:
```sh
sudo apt-get install build-essential  # Debian/Ubuntu
sudo dnf install gcc-c++              # Fedora/RHEL
```

### Apple Silicon (M1/M2/M3) Compatibility

This code currently only works on Intel x86 Macs due to the `-march=native` flag and OpenMP configuration. For Apple Silicon support, modifications to the Makefile would be needed.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Copyright (c) 2018 Semyon Fomin

## Contributing

This is a proof-of-concept project. Contributions, issues, and feature requests are welcome!

## Additional Resources

- [Sieve of Eratosthenes - Wikipedia](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)
- [OpenMP Documentation](https://www.openmp.org/)
- [Prime Number Theorem](https://en.wikipedia.org/wiki/Prime_number_theorem)
