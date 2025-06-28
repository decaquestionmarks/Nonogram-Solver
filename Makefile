CXXFLAGS=-std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic -ggdb

all: main

main: src/solver.o
	g++ $(CXXFLAGS) src/main.cpp bin/solver.o bin/nonogram.o -o main.exe

src/solver.o: src/nonogram.o
	g++ $(CXXFLAGS) -c src/solver.cpp bin/nonogram.o -o bin/solver.o

src/nonogram.o:
	g++ $(CXXFLAGS) -c src/nonogram.cpp -o bin/nonogram.o

clean:
	rm -rf main src/*.0

test: src/solver.o
	g++ $(CXXFLAGS) src/test.cpp bin/solver.o bin/nonogram.o -o test.exe