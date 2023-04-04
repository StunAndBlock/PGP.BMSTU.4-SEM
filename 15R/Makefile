all:15R

15R: 15R.o win15RHandler.o env15RHandler.o inform.o 
	cc -o 15R 15R.o win15RHandler.o env15RHandler.o inform.o -lX11 

15R.o: 15R.c
	cc -c 15R.c 

win15RHandler.o: win15RHandler.c
	cc -c win15RHandler.c 
env15RHandler.o:env15RHandler.c 
	cc -c env15RHandler.c 
inform.o: inform.c
	cc -c inform.c

clean:
	rm -rf *.o
