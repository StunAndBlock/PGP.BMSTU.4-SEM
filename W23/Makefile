all:W23
W23: W23.o winW23Handler.o envW23Handler.o 
	cc -o W23 W23.o winW23Handler.o envW23Handler.o -lX11 

W23.o:W23.c 
	cc -c W23.c 
winW23Handler.o: winW23Handler.c 
	cc -c winW23Handler.c 
envW23Handler.o: envW23Handler.c 
	cc -c envW23Handler.c 
 
clean:
	rm -rf *.o