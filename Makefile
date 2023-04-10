all:8S

8S: 8S.o win8SH.o env8SH.o
	cc -o build/8S 8S.o win8SH.o env8SH.o -lX11 -g

8S.o: 8S.c
	cc -c 8S.c -g

win8SH.o: win8SH.c
	cc -c win8SH.c -g
env8SH.o:env8SH.c 
	cc -c env8SH.c -g

clean:
	rm -rf *.o build/8S
rebuild: clean 8S