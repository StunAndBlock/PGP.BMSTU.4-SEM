all: 1M
1M: 1M.o 1Mblock.o 
	cc -o 1M 1M.o 1Mblock.o -lX11 -lm -g
1M.o: 1M.c
	cc -c 1M.c -g -lX11
1Mblock.o: 1Mblock.c
	cc -c 1Mblock.c -g -lX11

clean:
	rm -rf *.o

exec:
	rm -rf 1M

rebuild: clean exec all 	


