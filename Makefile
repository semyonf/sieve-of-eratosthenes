.PHONY: md5 js cxx

cxx: bin/eratosthenes
	if [ ! -d 'out' ]; then mkdir 'out'; fi
	./bin/eratosthenes > out/cxx.txt
	# cat out/cxx.txt

bin/eratosthenes: eratosthenes.cxx
	if [ ! -d 'bin' ]; then mkdir 'bin'; fi
	clang -lc++ -std=c++14 -O3 -flto -march=native -Wall -Wextra -pedantic eratosthenes.cxx -o bin/eratosthenes

js:
	if [ ! -d 'out' ]; then mkdir 'out'; fi
	node eratosthenes.js > out/js.txt
	# cat out/js.txt

md5: cxx js
	md5 out/*