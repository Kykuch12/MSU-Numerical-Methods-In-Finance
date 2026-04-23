OPTS = -O3 -g -Wall -Wextra -Wunused -Werror -pedantic -std=c++11

all: prog

prog: main.o chebyshev.o
	g++ $(OPTS) main.o chebyshev.o -o prog
main.o: main.cpp chebyshev.hpp
	g++ -c $(OPTS) main.cpp
chebyshev.o: chebyshev.cpp chebyshev.hpp
	g++ -c $(OPTS) chebyshev.cpp

clean:
	rm -f main.o chebyshev.o  prog