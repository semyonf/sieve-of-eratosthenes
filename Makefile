.PHONY: cxx clean

# Compiler flags for optimization and warnings
COMPILER_FLAGS = -std=c++17 -O3 -flto -march=native -Wall -Wextra -pedantic

# Security hardening flags
SECURITY_FLAGS = -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wformat-security

# Platform-specific OpenMP flags for macOS
CLANG_OMP_FLAGS = -Xpreprocessor -fopenmp -lomp

cxx: bin/eratosthenes
	@if [ ! -d 'out' ]; then mkdir 'out'; fi
	./bin/eratosthenes > out/primes.txt
	@cat out/primes.txt

bin/eratosthenes: eratosthenes.cxx Makefile
	@if [ ! -d 'bin' ]; then mkdir 'bin'; fi
ifeq ($(shell uname), Darwin)
	clang++ $(COMPILER_FLAGS) $(SECURITY_FLAGS) $(CLANG_OMP_FLAGS) eratosthenes.cxx -o bin/eratosthenes
else
	g++ $(COMPILER_FLAGS) $(SECURITY_FLAGS) -fopenmp eratosthenes.cxx -o bin/eratosthenes
endif

clean:
	rm -rf bin out
