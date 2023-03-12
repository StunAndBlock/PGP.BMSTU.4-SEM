all:W07
W07: W07_C winW07Handler_C numW07Handler_C 
	cc -o W07 W07.o winW07Handler.o numW07Handler.o -lX11 
W07_C:
	cc -c W07.c 

winW07Handler_C: 
	cc -c winW07Handler.c 


numW07Handler_C:
	cc -c numW07Handler.c 


clean:
	rm -rf *.o