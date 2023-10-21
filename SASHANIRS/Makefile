all:combinations
combinations: combinations_C winCombinations_C numCombinations_C 
	cc -o combinations combinations.o winCombinations.o numCombinations.o -lX11 -g -lm
combinations_C:
	cc -c combinations.c -g

winCombinations_C: 
	cc -c winCombinations.c -g 


numCombinations_C:
	cc -c numCombinations.c -g 


clean:
	rm -rf *.o