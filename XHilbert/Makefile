

all: main logic_implementations gi_implementations
	g++ main.o logic_implementations.o gi_implementations.o -lm -g -lX11 --std=c++11 -o ./build/hilbert 

main: main.cpp 
	g++ -c main.cpp gi_class.hpp logic_class.hpp

logic_implementations: logic_implementations.cpp logic_class.hpp
	g++ -c logic_implementations.cpp
gi_implementations: gi_implementations.cpp gi_class.hpp
	g++ -c gi_implementations.cpp


clean:
	rm -rf *.o *.gch ./build/hilbert 

rebuild: clean all
