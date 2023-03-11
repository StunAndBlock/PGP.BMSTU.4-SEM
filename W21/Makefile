all:W21
W21: W21_C winW21Handler_C INFORM_C envW21Handler_C 
	cc -o W21 W21.o winW21Handler.o envW21Handler.o inform.o -lX11 

W21_C:
	cc -c W21.c 

winW21Handler_C: 
	cc -c winW21Handler.c 
envW21Handler_C:
	cc -c envW21Handler.c 


INFORM_C:
	cc -c inform.c 