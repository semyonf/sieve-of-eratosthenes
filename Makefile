.PHONY: all js cxx

all: cxx js
	md5 out/*

cxx: bin/exec
	if [ ! -d 'out' ]; then mkdir 'out'; fi
	./bin/exec > out/cxx.txt
	# cat out/cxx.txt

bin/exec: main.cxx
	if [ ! -d 'bin' ]; then mkdir 'bin'; fi
	clang -lc++ -std=c++14 -O3 -flto -Wall -Wextra -pedantic main.cxx -o bin/exec

js:
	if [ ! -d 'out' ]; then mkdir 'out'; fi
	node main.js > out/js.txt
	# cat out/cxx.txt