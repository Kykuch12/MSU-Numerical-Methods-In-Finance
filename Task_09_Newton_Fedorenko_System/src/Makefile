OPTS = -O3 -g -Wall -Wextra -Wunused -Werror -pedantic -std=c++11

all: prog

prog: main.o newton.o
	g++ $(OPTS) main.o newton.o -o prog
main.o: main.cpp newton.hpp
	g++ -c $(OPTS) main.cpp
newton.o: newton.cpp newton.hpp
	g++ -c $(OPTS) newton.cpp

clean:
	rm -f main.o newton.o  prog