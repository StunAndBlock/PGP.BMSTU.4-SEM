all:8S

8S: 8S.o win8SH.o env8SH.o
	cc -o build/8S 8S.o win8SH.o env8SH.o  -lX11 

8S.o: 8S.c
	cc -c 8S.c 

win8SH.o: win8SH.c
	cc -c win8SH.c 
env8SH.o:env8SH.c 
	cc -c env8SH.c 

clean:
	rm -rf *.o 8S
rebuild: clean 8S