all:R4

R4: R4.o winR4H.o envR4H.o
	cc -o build/R4 R4.o winR4H.o envR4H.o  -lX11  -g

R4.o: R4.c
	cc -c R4.c -g

winR4H.o: winR4H.c
	cc -c winR4H.c  -g
envR4H.o:envR4H.c 
	cc -c envR4H.c -g

clean:
	rm -rf *.o R4
rebuild: clean R4