all:W28
W28: W28.o winW28Handler.o envW28Handler.o inform.o 
	cc -o W28 W28.o winW28Handler.o envW28Handler.o inform.o -lX11

W28.o: W28.c
	cc -c W28.c 

winW28Handler.o: winW28Handler.c
	cc -c winW28Handler.c 
envW28Handler.o:envW28Handler.c 
	cc -c envW28Handler.c 

inform.o: inform.c
	cc -c inform.c 

clean:
	rm -rf *.o