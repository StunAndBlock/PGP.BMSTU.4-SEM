all:main
main: main.o practice.o practice_visual.o
	g++ -o build/graph main.o practice.o practice_visual.o -lX11 -lm -g

main.o: main.cpp practice.h
	g++ -c main.cpp -g

practice.o: practice.cpp
	g++ -c practice.cpp -g

practice_visual.o: practice_visual.cpp
	g++ -c practice_visual.cpp -g


clean:
	rm -rf *.o build/graph

rebuild: clean all