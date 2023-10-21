all:combinations
combinations: combinations_C winCombinations_C numCombinations_C 
	cc -o combinations combinations.o winCombinations.o numCombinations.o -lX11 
combinations_C:
	cc -c combinations.c 

winCombinations_C: 
	cc -c winCombinations.c 


numCombinations_C:
	cc -c numCombinations.c 


clean:
	rm -rf *.o