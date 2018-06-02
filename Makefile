.PHONY: md5 js cxx clean

COMPILER_FLAGS = -std=c++17 -O3 -flto -march=native -Wall -Wextra -pedantic
CLANG_OMP_FLAGS = -Xpreprocessor -fopenmp -lomp

cxx: bin/eratosthenes
	@if [ ! -d 'out' ]; then mkdir 'out'; fi
	./bin/eratosthenes > out/cxx.txt
	@cat out/cxx.txt

bin/eratosthenes: eratosthenes.cxx Makefile
	@if [ ! -d 'bin' ]; then mkdir 'bin'; fi
ifeq ($(shell uname), Darwin)
	####################################################
	### For OpenMP on Macintosh: brew install libomp ###
	####################################################
	clang++ $(COMPILER_FLAGS) $(CLANG_OMP_FLAGS) eratosthenes.cxx -o bin/eratosthenes
else
	g++ $(COMPILER_FLAGS) eratosthenes.cxx -o bin/eratosthenes
endif

js:
	@if [ ! -d 'out' ]; then mkdir 'out'; fi
	node eratosthenes.js > out/js.txt
	@cat out/js.txt

md5: cxx js
	md5 out/*

clean:
	rm -rf bin out
