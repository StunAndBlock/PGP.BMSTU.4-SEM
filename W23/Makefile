all:W23
W21: W23_C winW23Handler_C envW23Handler_C 
	cc -o W23 W23.o winW23Handler.o envW23Handler.o -lX11 

W21_C:
	cc -c W23.c 

winW21Handler_C: 
	cc -c winW23Handler.c 
envW21Handler_C:
	cc -c envW23Handler.c 
 
clean:
	rm -rf *.o