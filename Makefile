CXX = g++
CXXFLAGS = -std=c++20

all: main #test

main: Player.o Game.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

test: Player.o Game.o test.cpp
	$(CXX) $(CXXFLAGS) test.cpp -o test

Game: Game.cpp main
	$(CXX) $(CXXFLAGS) Game.cpp -c

Player: Player.cpp main
	$(CXX) $(CXXFLAGS) Player.cpp -c
clean:
	-rm -f Game.o Player.o main test
run:
	make clean --no-print-directory
	make all --no-print-directory
	./main