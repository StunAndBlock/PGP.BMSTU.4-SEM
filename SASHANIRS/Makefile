
all:combinations
combinations: combinations.o winCombinations.o numCombinations.o choose.o
	cc -o build/combinations combinations.o winCombinations.o numCombinations.o choose.o -lX11 -lm
combinations.o: combinations.c combinations.h
	cc -c combinations.c

winCombinations.o: winCombinations.c
	cc -c winCombinations.c

numCombinations.o: numCombinations.c
	cc -c numCombinations.c

choose.o: choose.c choose.h
	cc -c choose.c 

clean:
	rm -rf *.o build/combinations