all:24S

24S: 24S.o win24SHandler.o env24SHandler.o inform.o 
	cc -o 24S 24S.o win24SHandler.o env24SHandler.o inform.o -lX11 

24S.o: 24S.c
	cc -c 24S.c 

win24SHandler.o: win24SHandler.c
	cc -c win24SHandler.c 
env24SHandler.o:env24SHandler.c 
	cc -c env24SHandler.c 
inform.o: inform.c
	cc -c inform.c

clean:
	rm -rf *.o